#include <stdio.h>
#include <unistd.h>

char y;
char z1 = 1;
const char c = 2;

void printLoc(void) {
  char x = 5;
  printf("loc -- %p\n", &x);
}

void printStat(void) {
  static char x = 6;
  printf("stat -- %p\n", &x);
}

void printConst(void) {
  const char x = 7;
  printf("const -- %p\n", &x);
}

void printGloNotInit(void) { printf("gloNotInit -- %p\n", &y); }

void printGloInit(void) { printf("gloInit -- %p\n", &z1); }

void printGloConst(void) { printf("gloConst -- %p\n", &c); }

char* locVar(void) {
	char x = 15;
	printf("%p\n", &x);
	return &x;
}

int main(void) {
  char ch;
  printLoc();
  printStat();
  printConst();
  printGloNotInit();
  printGloInit();
  printGloConst();
	printf("%p\n", locVar());
	printf("pid -- %d\n", getpid());
  scanf("%c", &ch);
  return 0;
}
