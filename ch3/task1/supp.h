#pragma once

#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

#define bufSize 1024

void reverse(char* string, int len);
DIR* prepareDir(char** argv);
void revText(struct stat sb, FILE* baseFile, FILE* newFile);
char* createNewPath(char* newName, char* path, char* revName);