#include "procWithName.h"
#include "supp.h"
#include "mem.h"

#define pathD "/home/pyro/Desktop/os/ch3/"

void reverse(char* string, int len) {
    for (int i = 0; i < len/2; ++i) {
        char mem = string[i];
        string[i] = string[len-i-1];
        string[len-i-1] = mem;
    }
}

DIR* prepareDir(char** argv) {
    DIR *tempDir = opendir(argv[1]);

    if (tempDir == NULL) {
        fprintf(stderr, "Error in first supp opendir: %s\n", strerror(errno));
        return NULL;
    }

    struct stat sb;

    if (stat(argv[1], &sb)) {
        fprintf(stderr, "Error in first supp stat: %s\n", strerror(errno));
        closedir(tempDir);
        return NULL;
    }

    char* revName = getName(argv); int pathLen = strlen(pathD); 
    char* bufName = (char*)calloc(strlen(revName)+pathLen, sizeof(char));
    sprintf(bufName, "%s", pathD); sprintf(bufName+pathLen, "%s", revName);

    if (mkdir(bufName, sb.st_mode)) {
        fprintf(stderr, "Error in first supp mkdir: %s\n", strerror(errno));
        if (revName != NULL) freeAdr(&revName); free(bufName);
        closedir(tempDir);
        return NULL;
    }

    if (revName != NULL) freeAdr(&revName); free(bufName);
    return tempDir;
}

void revText(struct stat sb, FILE *baseFile, FILE *newFile) {
    char* buffer = (char*)calloc(bufSize, sizeof(char));
    size_t readSym;

    long int i = sb.st_size;

    fseek(baseFile, 0, SEEK_END);

    while (i) {
        if (i >= bufSize){
            fseek(baseFile, -bufSize, SEEK_CUR);
            readSym = fread(buffer, sizeof(char), bufSize, baseFile);
            i -= bufSize;
        } else {
            fseek(baseFile, 0, SEEK_SET);
            readSym = fread(buffer, sizeof(char), i, baseFile);
            i = 0;
        }

        reverse(buffer, readSym);
        fwrite(buffer, sizeof(char), readSym, newFile);
        fseek(baseFile, -readSym, SEEK_CUR);
    }

    free(buffer);
}

char* createNewPath(char* newName, char* path, char* revName) {
    char* name = cut(path);
    size_t len = strlen(name);

    for (int i = 0; i < len; ++i) {
        newName[i] = name[len-1-i];
    }

    char* res = makePath(revName, newName);
    free(name);

    return res;
}