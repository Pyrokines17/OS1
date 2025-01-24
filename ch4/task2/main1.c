#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#define sizeB 4096
#define count 25

#define errorOfMmap 1
#define errorOfMprotect 2
#define errorOfMunmap 3
#define errorOfHandler 4

void func() {
  char var[sizeB];
	sleep(1);
  func();
}

void hand(int i) {
  printf("signal catch after trying do sth from mprotect\n");
  exit(errorOfHandler);
}

int main(int argc, char** argv) {
	char ch;

  printf("pid -- %d\n", getpid());
  
	printf("brpoint");
	scanf("%c", &ch);
  
	if (strcmp(argv[1], "1") == 0) {
		func();
	}

  char *mas[count];

	printf("brpoint");
	scanf("%c", &ch);

  for (int i = 0; i < count; ++i) {
    mas[i] = malloc(sizeof(char) * sizeB * 10);
    sleep(1);
  }

  for (int i = 0; i < count; ++i) {
    free(mas[i]);
  }
	
	printf("brpoint");
	scanf("%c", &ch);
  
	char *resOfMmap = mmap(NULL, getpagesize() * 10, PROT_EXEC, MAP_ANON | MAP_SHARED, -1, 0);

  if (resOfMmap == MAP_FAILED) {
    printf("Error in mmap: %s\n", strerror(errno));
    return errorOfMmap;
  }

	printf("brpoint");
	scanf("%c", &ch);

  if (mprotect(resOfMmap, getpagesize() * 10, PROT_NONE)) {
    printf("Error in mprotect №1: %s\n", strerror(errno));
    return errorOfMprotect;
  }

	char x;

	if (strcmp(argv[2], "r") == 0) {
		signal(SIGSEGV, &hand);
		x = resOfMmap[1];
	}

  if (mprotect(resOfMmap, getpagesize() * 10, PROT_NONE)) {
    printf("Error in mprotect №2: %s\n", strerror(errno));
    return errorOfMprotect;
  }

	if (strcmp(argv[2], "w") == 0) {
		signal(SIGSEGV, &hand);
		resOfMmap[0] = 'a';
	}

  if (munmap(resOfMmap + getpagesize() * 3, getpagesize() * 3)) {
    printf("Error in munmap: %s\n", strerror(errno));
    return errorOfMunmap;
  }

	printf("finish");
	scanf("%c", &ch);

  return 0;
}
