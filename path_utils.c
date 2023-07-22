#include "shell.h"

/**
 * ispath - checks if the program name is a path or not
 * @prgname: the program name and the argv first element
 *
 * Return: 1 if it's a path
 * 0 otherwise
 */

int ispath(char *prgname)
{
	int i = 0;

	while (prgname[i])
	{
		if (prgname[i] == '/')
			return (1);
		i++;
	}

	return (0);
}

/**
 * getprgpath - checks if the program exists in any of the paths in
 * the PATH environment variable
 * @prgname: the programe name
 *
 * Return: pointer to the first path contains the program
 * NULL on failure
 */

char *getprgpath(char *prgname)
{
	char *pathenv = NULL, *path = NULL, *prgpath = NULL;
	int pathscount = 0;
	char delim = ':';
	struct stat info;

	pathenv = getenval("PATH");
	if (pathenv != NULL)
	{
		pathscount = wordscount(pathenv, &delim);
		if (pathscount > 0)
		{
			pathenv = cpystr(pathenv); /* need to be freed */
			path = strtok(pathenv, &delim);
			while (path != NULL)
			{
				prgpath = makeprgpath(path, prgname);/*to free*/
				if (stat(prgpath, &info) == 0)
					return (prgpath);
				free(prgpath); /* = prgpath in makeprgpath*/
				path = strtok(NULL, &delim);
			}
			/*paths[i] = NULL;*/
		}
	}
		free(pathenv);
		return (NULL);
}

/**
 * makeprgpath - appends program name to a path
 * @path: path doesn't end with '/' like in the PATH
 * @prgname: the name of the program
 *
 * Return: pointer to the whole path
 */

char *makeprgpath(char *path, char *prgname)
{
	char *prgpath = NULL, *strp = NULL;
	int pathlen = 0, prgnamelen = 0, i = 0;

	pathlen = strlen(path);
	prgnamelen = strlen(prgname);
	prgpath = malloc(pathlen + prgnamelen + 2);
	if (prgpath == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	strp = path;
	while (*strp)
	{
		prgpath[i++] = *strp;
		strp++;
	}
	prgpath[i++] = '/';
	strp = prgname;
	while (*strp)
	{
		prgpath[i++] = *strp;
		strp++;
	}
	prgpath[i] = '\0';

	return (prgpath);
}

