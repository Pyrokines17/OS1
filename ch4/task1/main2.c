#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define errorOfEnv 1
#define errorOfSetEnv 2

#define name "VAR"
#define a "15"

int main(int argc, char **argv) {
  char *var = getenv(name);
  printf("%p\n", &var[0]);

  if (var) {
    printf("%s\n", var);
  } else {
    printf("Name not found: %s\n", name);
    return errorOfEnv;
  }

  if (setenv(name, a, 1)) {
    printf("Error in setenv: %s\n", strerror(errno));
    return errorOfSetEnv;
  }

  char *var1 = getenv(name);

  if (var1) {
    printf("%s\n", var1);
  } else {
    printf("Name not found: %s\n", name);
    return errorOfEnv;
  }

  printf("%d\n", getpid());

  char ch;
  scanf("%c", &ch);

  return 0;
}
