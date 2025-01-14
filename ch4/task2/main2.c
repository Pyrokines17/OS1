#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define error 1

int main(int main, char** argv) {
  printf("pid -- %d\n", getpid());
  sleep(1);

  if (execl(argv[0], argv[0], NULL)) {
    printf("Error in execl: %s\n", strerror(errno));
    exit(error);
  }

  printf("Hello world\n");
  return 0;
}
