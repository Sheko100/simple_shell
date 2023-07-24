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

	len = lenstr(s);
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

/**
 * cmpstr - compares two strings if they are identical or not
 * @s1: first str
 * @s2: second str
 *
 * Return: 1 if the strings are identical
 * 0 otherwise
 */

int cmpstr(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}

	return (1);
}

/**
 * lenstr - Counts the length of the string excluding the null byte
 * @s: pointer to a string
 *
 * Return: string length
 */

int lenstr(char *s)
{
	int len = 0;

	while (s[len])
		len++;

	return (len - 1);
}
