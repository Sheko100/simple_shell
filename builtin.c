#include "shell.h"

/**
 * printenvs - prints the environment variables to the standard output
 *
 * Return: 1 on success
 * -1 on failure
 */

int printenvs(void)
{
	char **ep = NULL;

	ep = environ;

	while (*ep)
	{
		if (write(STDOUT_FILENO, *ep, lenstr(*ep)) == -1)
			return (-1);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (-1);
		ep++;
	}

	return (1);
}
