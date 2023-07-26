#include "shell.h"

/**
 * endline - replaces the new line byte written by pushing the enter button
 * with a null byte
 * @line: pointer to cmd line ends with \n
 * @newlipos: the \n index position
 *
 * Return: 1 on success
 * 0 on failure
 */

int endline(char *line, int newlipos)
{
	int status = 1;

	if (line[newlipos] == '\n' || line[newlipos] == ' ')
		line[newlipos] = '\0';
	else
		status = 0;

	return (status);
}

/**
 * splitcmd - splits the whole command to seperated words
 * @cmd: buffer conatins the command to split
 *
 * Return: pointer to the first byte of words memory space
 */

char **splitcmd(char *cmd)
{
	char delim[2] = {9, 32};
	int wordsnum = 0, i = 0;
	char *token = NULL, **words = NULL;

	wordsnum = wordscount(cmd, delim);
	if (wordsnum == 0)
		return (NULL);

	words = malloc(sizeof(char *) * (wordsnum + 1)); /* need to be freed */
	if (words == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(cmd, delim);
	while (token != NULL)
	{
		*(words + i) = token;
		token = strtok(NULL, delim);
		i++;
	}
	*(words + i) = NULL;

	return (words);
}

/**
 * wordscount - counts the number of words seperated by
 * the specified delimeter
 * @str: pointer to the command line string
 * @delim: array of char bytes to seperate the words
 *
 * Return: number of words in the command line
 */

int wordscount(char *str, char delim[])
{
	int count = 0;
	char *newstr, *word;

	newstr = cpystr(str); /* need to be freed */

	word = strtok(newstr, delim);

	while (word != NULL)
	{
		count++;
		word = strtok(NULL, delim);
	}

	free(newstr);  /* = newstr in cpystr - freed */

	return (count);
}
