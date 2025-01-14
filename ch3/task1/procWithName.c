#include "procWithName.h"
#include "supp.h"

char* cut(char* string) {
    size_t len = strlen(string);
    char *result, *retS;
    size_t count;

    if (string[len - 1] == '/') {
        string[len - 1] = 0;
        len -= 1;
    }

    retS = strrchr(string, '/');

    if (retS != NULL) {
        count = len - (size_t)(retS - string + 1);
        result = (char *)calloc(count, sizeof(char));

        for (int i = 0; i < count; ++i) {
            result[i] = string[retS - string + 1 + i];
        }

    } else {

        count = len;
        result = (char *)calloc(count, sizeof(char));

        for (int i = 0; i < count; ++i) {
            result[i] = string[i];
        }
    }

    return result;
}

char* makePath(char* base, char* name) {
    size_t lenBase = strlen(base),
            lenName = strlen(name),
            len = lenBase + lenName;

    if (base[lenBase - 1] != '/') {
        len += 1;
    }

    char *result = (char *)calloc(len, sizeof(char));
    sprintf(result, "%s", base);

    if (base[lenBase - 1] != '/') {
        result[lenBase] = '/';
    }

    sprintf(result + len - lenName, "%s", name);
    return result;
}

char* getName(char** argv) {
    char* name = cut(argv[1]);
    reverse(name, strlen(name));
    return name;
}