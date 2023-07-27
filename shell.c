#include "shell.h"

/**
 * shell - starts the shell either in interactive or not-interactive
 * @shname: the path of the shell when executing
 * @isinteractv: either 1 or 0 to
 * choose the mode of interactive or not-interactive
 *
 * Return: 0 on success
 * -1 on error
 */

int shell(char *shname, int isinteractv)
{
	int readbytes, l, i = 1, linescount = 0;
	char buf[BUFSIZE];
	char **lines = NULL, *line = NULL;

	if (isinteractv)
		write(STDOUT_FILENO, "#wish$ ", 7);
	while ((readbytes = read(STDIN_FILENO, buf, BUFSIZE)) > 0)
	{
		if (readbytes == 1 && isinteractv)
		{
			write(STDOUT_FILENO, "#wish$ ", 7);
			i++;
			continue;
		}
		if (!endline(buf, readbytes - 1))
			exit(EXIT_FAILURE);
		linescount = wordscount(buf, "\n");
		if (linescount > 0)
			lines = malloc(sizeof(char *) * (linescount + 1));
		if (lines == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		} l = 0;
		line = strtok(buf, "\n");
		while (line != NULL)
		{
			lines[l++] = line;
			line = strtok(NULL, "\n");
		}
		lines[l] = NULL;
		interpretline(shname, lines, linescount, isinteractv);
		free(lines);
		if (isinteractv)
			write(STDOUT_FILENO, "#wish$ ", 7);
		i++;
	}
	if (isinteractv)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/**
 * interpretline - Interpretes line, splits it and try to execute it
 * @shname: the name of the shell
 * @lines: a NULL terminated array of lines
 * @linescount: the count of lines
 * @isinteractv: either 0 or 1 to detremine the mode
 *
 * Return: 0 on success
 */

int interpretline(char *shname, char **lines, int linescount, int isinteractv)
{
	char **argv = NULL, *prgpath = NULL;
	int status, isexist = 1, i = 0, exitstatus = 0;

	while (lines[i])
	{ argv = splitcmd(lines[i]);
		if (argv != NULL)
		{
			if (isbuiltin(argv, lines, exitstatus) == 0)
			{
				if (ispath(argv[0]) == 0)
				{
					prgpath = getprgpath(argv[0]);
					if (prgpath)
						argv[0] = prgpath;
					else
						isexist = 0;
				}
				if (linescount > 1)
				{
					if (fork() == 0)
					{ execprg(argv, shname, isinteractv, isexist);
						exit(EXIT_FAILURE);
					}
					else
					{ wait(&status);
						exitstatus = WEXITSTATUS(status);
					}
				}
				else
				{
					if (execprg(argv, shname, isinteractv, isexist) == -1)
					{ free(argv);
						free(lines);
						exit(EXIT_FAILURE);
					}
				} free(prgpath);
			} free(argv); /* = words in splitcmd - freed */
		} i++;
	}
	return (exitstatus);
}

/**
 * execprg - executes a program
 * @argv: a NULL terminated array contains the program name and its arguments
 * @shname: the name of the shell
 * @isinteractv: either 0 or 1 to
 * detrmine which to create a child process or not
 * @isexist: either 0 or 1 to detrmine if the program was found or not
 *
 * Return: 0 on success
 */

int execprg(char **argv, char *shname, int isinteractv, int isexist)
{
	pid_t childpid = 0;
	int status;

	if (isinteractv && isexist)
	{
		childpid = fork();
		if (childpid == -1)
		{
			perror("Creating child process");
			exit(EXIT_FAILURE);
		}

		if (childpid == 0)
		{
			execve(argv[0], argv, environ);
			free(argv);
			perror(shname);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (wait(&status) != -1)
			{
				return (0);
			}
			perror("wait");
		}
	}

	execve(argv[0], argv, environ);
	perror(shname);

	return (-1);
}

/**
 * isbuiltin - checks if the command is a built-in and execute the associated
 * function
 * @argv: array of arguments strings
 * @lines: array of lines to free in exit case
 * @exitstatus: exist status code
 *
 * Return: 1 if the command is a built-in
 * 0 otherwise
 */

int isbuiltin(char **argv, char **lines, int exitstatus)
{
	int status = 0;
	char *cmd = argv[0];

	if (cmpstr(cmd, "exit"))
	{
		free(lines);
		exitshell(exitstatus, argv);
	}
	else if (cmpstr(cmd, "env"))
	{
		status = 1;
		printenvs();
	}

	return (status);
}
