#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *file;
    char buffer[BUFFER_SIZE];

    file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("File contents:\n");
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        printf("%s", buffer);
    }

    printf("\nReal user ID: %d\n", getuid());
    printf("Effective user ID: %d\n", geteuid());

    fclose(file);

    return 0;
}