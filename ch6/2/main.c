#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define error 1

int main(void) {
    int page = getpagesize();
    unsigned int *mem = malloc(page), *mem1 = malloc(page);
    int border = page / sizeof(unsigned int);

    int p[2];

    if (pipe(p) == -1) {
        fprintf(stderr, "Error in pipe: %s\n", strerror(errno));
        exit(error);
    }

    pid_t res = fork();

    if (res == -1) {
        fprintf(stderr, "Error in fork: %s\n", strerror(errno));
        exit(error);
    } else if (res == 0) {
        unsigned int i = 0;

        while (1) {
            mem[i%border] = i;
            ++i;

            write(p[1], mem, page);
        }
    } else {
        unsigned int i1 = 0;

        while (1) {
            read(p[0], mem1, page);

            int dif = mem1[(i1+1)%border] - mem1[i1%border];

            if (dif != 1 && dif != -1023) {
                printf("Diff: %u, %u, %d\n", mem1[i1%border], mem1[(i1+1)%border], dif);
            } 

            ++i1;
        }
    }
}