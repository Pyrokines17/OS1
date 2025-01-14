#include <stdio.h>
#include <unistd.h>

int main(void) {
	write(1, "Hello, world!", 13);

	return 0;
}