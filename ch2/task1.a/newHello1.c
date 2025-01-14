#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>

int sysWrite(char* string);

int main(void) {
	sysWrite("Hello, world!");

	return 0;
}

int sysWrite(char* string) {
	int len = strlen(string);
	return syscall(SYS_write, 1, string, len);
}