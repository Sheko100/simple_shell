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
	int readbytes, i = 1, isexist;
	char **argv = NULL, *prgpath = NULL, buf[BUFSIZE];

	if (isinteractv)
		write(STDOUT_FILENO, "#wish$ ", 7);
	while ((readbytes = read(STDIN_FILENO, buf, BUFSIZE)) > 0)
	{
		isexist = 1;
		if (readbytes == 1 && isinteractv)
		{
			write(STDOUT_FILENO, "#wish$ ", 7);
			i++;
			continue;
		}
		if (!endline(buf, readbytes - 1))
			exit(EXIT_FAILURE);
		argv = splitcmd(buf);
		if (argv != NULL)
		{
			if (isbuiltin(argv) == 0)
			{
				if (ispath(argv[0]) == 0)
				{
					prgpath = getprgpath(argv[0]);
					if (prgpath)
						argv[0] = prgpath;
					else
						isexist = 0;
				}
				execprg(argv, shname, isinteractv, isexist);
				free(prgpath);
				free(argv); /* = words in splitcmd - freed */
			}
		}
		if (isinteractv)
			write(STDOUT_FILENO, "#wish$ ", 7);
		i++;
	}
	if (isinteractv)
		write(STDOUT_FILENO, "\n", 1);

	return (0);
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
	}

	if (childpid == 0)
		execve(argv[0], argv, environ);
	else
	{
		if (wait(&status) != -1)
			return (0);
		perror("wait");
	}

	perror(shname);
	return (-1);
}

/**
 * isbuiltin - checks if the command is a built-in and execute the associated
 * function
 * @argv: array of arguments strings
 *
 * Return: 1 if the command is a built-in
 * 0 otherwise
 */

int isbuiltin(char **argv)
{
	int status = 0;
	char *cmd = argv[0];

	if (cmpstr(cmd, "exit"))
	{
		free(argv);
		exit(EXIT_SUCCESS);
	}

	return (status);
}
