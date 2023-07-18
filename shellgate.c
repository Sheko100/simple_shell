#include "shell.h"

/**
 * main - shell entry point and checker if it either should run in
 * interactive mode or not interactive mode
 * @ac: arguments count
 * @av: arguments values
 *
 * Return: 0 always
 */

int main(int ac, char **av)
{
	if (isatty(STDIN_FILENO))
	{
		shell(av[0], INTERACTIVE);
	}
	else
	{
		shell(av[0], NOT_INTERACTIVE);
	}

	return (0);
}
