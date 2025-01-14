#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define startSize 100

#define errorOfMallock 1
#define errorOfEnv 2
#define errorOfSetEnv 3
#define errorOfHandler 4

#define name "VAR"
#define a "15"

void processing(int i) {
  printf("catch signal\n");
  exit(errorOfHandler);
}

int main(int argc, char **argv) {
  char *buf = (char *)malloc(sizeof(char) * startSize);

  if (buf == NULL) {
    printf("Error in malloc №1: %s\n", strerror(errno));
    return errorOfMallock;
  }

  sprintf(buf, "%s", "hello world");
  printf("%s\n", buf);

  free(buf);
  printf("%s\n", buf);

  char *buf1 = (char *)malloc(sizeof(char) * startSize);

  if (buf1 == NULL) {
    printf("Error in mallo №2c: %s\n", strerror(errno));
    return errorOfMallock;
  }

  sprintf(buf, "%s", "hello world from buf");
  sprintf(buf1, "%s", "hello world from buf1");

  printf("%s\n", buf);
  printf("%s\n", buf1);

  buf1 = *(&buf1 + startSize / 2);

	signal(SIGSEGV, &processing);
	//free(buf1);

  printf("%s\n", buf);
  printf("%s\n", buf1);

  char *var = getenv(name);

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

  return 0;
}
