#include <unistd.h>
#include <stdio.h>

int main() {
    int newfd;

    // Duplicate stdout (file descriptor 1)
    newfd = dup(1);
    if (newfd == -1) {
        perror("dup");
        return 1;
    }

    // Now, newfd is a duplicate of stdout

    // Example write to stdout
    printf("This will be written to the original stdout\n");

    // Example write to newfd (duplicate of stdout)
    dprintf(newfd, "This will be written to the duplicated stdout\n");

    // Close the duplicated file descriptor
    close(newfd);

    return 0;
}

