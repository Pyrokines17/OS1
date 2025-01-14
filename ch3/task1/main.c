#include "mem.h"
#include "supp.h"
#include "procWithName.h"

#define pathD "/home/pyro/Desktop/os/ch3/"
#define errorNum 1

int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "Need dir...\n");
        return errorNum;
    }

    DIR* tempDir = prepareDir(argv);

    if (tempDir == NULL) {
        return errorNum;
    }

    char* revName = getName(argv); int pathLen = strlen(pathD); 
    char* bufName = (char*)calloc(strlen(revName)+pathLen, sizeof(char));
    sprintf(bufName, "%s", pathD); sprintf(bufName+pathLen, "%s", revName);

    struct stat sb; struct dirent* file;
    char *path = NULL, *newName = NULL, *newPath = NULL;

    while ((file = readdir(tempDir)) != NULL) {
        path = makePath(argv[1], file->d_name);

        if (stat(path, &sb)) {
            fprintf(stderr, "Error in first main stat: %s\n", strerror(errno));
            freeMem(&path, &newName, &newPath);
            continue;
        }

        if (!S_ISREG(sb.st_mode)) {
            freeMem(&path, NULL, NULL);
            continue;
        }

        FILE *baseFile = fopen(path, "rb");

        if (baseFile == NULL) {
            fprintf(stderr, "Error in first main fopen: %s\n", strerror(errno));
            freeMem(&path, &newName, &newPath);
            continue;
        }

        newName = (char*)calloc(strlen(file->d_name), sizeof(char));
        newPath = createNewPath(newName, path, bufName);

        FILE *newFile = fopen(newPath, "wb");

        if (newFile == NULL) {
            fprintf(stderr, "Error in second main fopen: %s\n", strerror(errno));
            freeMem(&path, &newName, &newPath);
            fclose(baseFile);
            continue;
        }

        revText(sb, baseFile, newFile);
        chmod(newPath, sb.st_mode);
        fclose(baseFile); fclose(newFile);
        freeMem(&path, &newName, &newPath);
    }

    if (revName != NULL) freeAdr(&revName);
    closedir(tempDir);
    free(bufName);

    return 0;
}
