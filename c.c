#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    pid_t cpid;
    char *ls_args[] = {"ls", NULL};
    char *sort_args[] = {"sort", NULL};

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    // Child reads from pipe
        close(pipefd[1]);          /* Close unused write end */

        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        execve("/usr/bin/sort", sort_args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);

    } else {            // Parent writes to pipe
        close(pipefd[0]);          /* Close unused read end */

        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        execve("/bin/ls", ls_args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    }

    return 0;
}
