#include "shell.h"

/**
 * getenval - searches for an environment variable and returns
 * a pointer to its value
 * @envname: the name of the environment variable
 *
 * Return: pointer to the start of env variable value if found
 * NULL if not found
 */

char *getenval(char *envname)
{
	char **ep;
	int i;

	ep = environ;

	while (ep)
	{
		i = 0;
		while (envname[i] == (*ep)[i])
		{
			if ((*ep)[i + 1] == '=' && (*ep)[i + 2] != '\0')
				return ((*ep) + (i + 2));
			i++;
		}
		ep++;
	}

	return (NULL);
}
