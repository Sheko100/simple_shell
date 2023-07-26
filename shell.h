#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>

#ifndef BUFSIZE
#define BUFSIZE 1024
#endif

#define INTERACTIVE 1
#define NOT_INTERACTIVE 0

extern char **environ;

int shell(char *shname, int isinteractv);
int isbuiltin(char **argv);
int printenvs(void);
int execprg(char **argv, char *shname, int isinteractv, int isexist);
int endline(char *line, int newlipos);
char **splitcmd(char *cmd);
char *cpystr(char *s);
int cmpstr(char *s1, char *s2);
int lenstr(char *s);
int wordscount(char *cmd, char delim[]);
int ispath(char *prgname);
char *getprgpath(char *prgname);
char *makeprgpath(char *path, char *prgname);
char *getenval(char *envname);
#endif

