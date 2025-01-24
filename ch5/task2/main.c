#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define error 1

int main(void) {
    char ch;
    int pid = getpid();
    printf("grandparent pid: %d\n", pid);

    printf("bpoint\n");
    scanf("%c", &ch);

    pid_t res = fork(), res1, w, w1;
    int status, status1;

    if (res == -1) {
        fprintf(stderr, "Error in fork: %s", strerror(errno));
        exit(error);
    } else if (res == 0) {
        int pid1 = getpid();
        printf("parent pid: %d\n", pid1);

        res1 = fork();

        if (res1 == -1) {
            fprintf(stderr, "Error in fork: %s", strerror(errno));
            exit(error);
        } else if (res1 == 0) {
            printf("child pid: %d\n", getpid());
            sleep(30);
            printf("child die...\n");
            exit(6);
        } else {
            sleep(15);
            printf("parent die...\n");
            exit(5);
        }
        
        exit(5);
    } else {
        printf("grandparent sleep...\n");
        sleep(60);

        printf("grandparent wakeup!\n");
        scanf("%c", &ch);
        
        w = waitpid(res, &status, 0);


        if (w == -1) {
            fprintf(stderr, "Error in waitpid: %s\n", strerror(errno));
            exit(error);
        }

        printf("Exit code in parent: %d\n", WEXITSTATUS(status));

        return 0;
    }
}