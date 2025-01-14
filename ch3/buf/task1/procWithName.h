#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* cut(char* string);
char* makePath(char* base, char* name);
char* getName(char** argv);