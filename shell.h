#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFSIZE
#define BUFSIZE 1024
#endif

#define INTERACTIVE 1
#define NOT_INTERACTIVE 0

int shell(char *shname, int isinteractv);
int endline(char *line, int newlipos);
char **splitcmd(char *cmd);
void freewords(char **words, char *firstbyte);
char *cpystr(char *s);
int wordscount(char *cmd);
#endif

