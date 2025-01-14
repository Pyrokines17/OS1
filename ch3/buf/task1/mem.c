#include "mem.h"

void freeAdr(char** str) {
    free(*str);
    *str = NULL;
}

void freeMem(char** path, char** newName, char** newPath) {
    if (path != NULL && *path != NULL) freeAdr(path);
    if (newName != NULL && *newName != NULL) freeAdr(newName);
    if (newPath != NULL && *newPath != NULL) freeAdr(newPath);
}