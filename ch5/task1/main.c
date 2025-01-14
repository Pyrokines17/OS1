#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define error 1

int x = 5;

int main(void) {
    int y = 10;
    char ch;

    printf("addr -- var:\n %p -- %d\n %p -- %d\n", &x, x, &y, y);

    int pid = getpid();

    printf("pid: %d\n", pid);

    printf("bpoint\n");
    scanf("%c", &ch);

    pid_t res = fork(), w;
    int status;

    if (res == -1) {
        fprintf(stderr, "Error in fork: %s", strerror(errno));
        exit(error);
    } else if (res == 0) {
        printf("my pid -- par pid:\n %d -- %d\n", getpid(), pid);
        printf("addr -- var in child:\n %p -- %d\n %p -- %d\n", &x, x, &y, y);
        printf("cbpoint1\n");
        scanf("%c", &ch);
        y = 9; x = 4;
        printf("addr -- var in child:\n %p -- %d\n %p -- %d\n", &x, x, &y, y);
        printf("cbpoint2\n");
        scanf("%c", &ch);
        exit(5);
    } else {
        printf("addr -- var in par:\n %p -- %d\n %p -- %d\n", &x, x, &y, y);
        sleep(30);
        printf("addr -- var in par:\n %p -- %d\n %p -- %d\n", &x, x, &y, y);

        printf("pbpoint\n");
        scanf("%c", &ch);
        
        w = waitpid(res, &status, 0);

        if (w == -1) {
            fprintf(stderr, "Error in waitpid: %s\n", strerror(errno));
            exit(error);
        }

        printf("Exit code: %d\n", WEXITSTATUS(status));

        return 0;
    }
}