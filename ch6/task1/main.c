#include <sys/mman.h>
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
    unsigned int *mem = mmap(NULL, page, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int border = page / sizeof(int);

    if (mem == MAP_FAILED) {
        fprintf(stderr, "Error in mmap: %s\n", strerror(errno));
        exit(error);
    }

    pid_t res = fork();

    if (res == -1) {
        fprintf(stderr, "Error in fork: %s\n", strerror(errno));
        exit(error);
    } else if (res == 0) {
        unsigned int i = 0,
            var = 0;

        while (1) {
            mem[i%border] = i;
            ++i; 
        }
    } else {
        unsigned int i1 = 0;

        while (1) {
            int dif = mem[(i1+1)%border]-mem[i1%border];

            if (dif != 1 && dif != -1023) {
                printf("Diff: %u, %u, %d\n", mem[i1%border], mem[(i1+1)%border], dif);
            } 

            ++i1;
        }
    }
}