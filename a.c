#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    printf("This text will be duplicated in the output file.\n");

    if (dup2(STDOUT_FILENO, fd) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    printf("This text will be printed to the terminal.\n");

    close(fd);
    while(1);
    return 0;
}
