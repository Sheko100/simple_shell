#include "shell.h"

/**
 * cpystr - copies string to a new dynamicly allocated memory
 * @s: pointer to a string
 *
 * Return: pointer to the new allocated memory contains the string
 */

char *cpystr(char *s)
{
	char *newstr = NULL;
	int len, i = 0;

	len = strlen(s);
	newstr = malloc(len + 1); /* need to be freed */
	if (newstr == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (s[i])
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';

	return (newstr);
}

