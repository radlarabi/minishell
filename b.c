#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct s_cmd_line {
    int infile;
    int outfile;
    char **cmds;
    struct s_cmd_line *next;
} t_cmd_line;

void execute_cmd(char **cmd, int in_fd, int out_fd) {
    if (execvp(cmd[0], cmd) < 0) {
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
}


void run_pipeline(t_cmd_line *pipeline) {
    int in_fd = STDIN_FILENO;
    int pipe_fd[2];
    pid_t pid;

    while (pipeline) {
        pipe(pipe_fd);

        pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // child process
            close(pipe_fd[0]);
            if (pipeline->infile != STDIN_FILENO) {
                in_fd = pipeline->infile;
            }
            if (pipeline->outfile != STDOUT_FILENO) {
                close(STDOUT_FILENO);
                dup2(pipe_fd[1], STDOUT_FILENO);
            }

            execute_cmd(pipeline->cmds, in_fd, pipe_fd[1]);
            close(pipe_fd[1]);
            exit(EXIT_SUCCESS);
        } else { // parent process
            close(pipe_fd[1]);
            if (pipeline->infile != STDIN_FILENO) {
                close(pipeline->infile);
            }
            if (in_fd != STDIN_FILENO) {
                close(in_fd);
            }

            in_fd = pipe_fd[0];
            close(pipe_fd[0]); // close the read end of the pipe
            pipeline = pipeline->next;
        }
    }

    if (in_fd != STDIN_FILENO) {
        dup2(in_fd, STDIN_FILENO);
    }
}



int main() {
    t_cmd_line *pipeline = malloc(sizeof(t_cmd_line));
    pipeline->infile = 4;
    pipeline->outfile = 4;
    char *cmd1[] = {"ls", "-l", NULL};
    char *cmd2[] = {"grep", ".c", NULL};
    pipeline->cmds = cmd1;
    pipeline->next = malloc(sizeof(t_cmd_line));
    pipeline->next->infile = 4;
    pipeline->next->outfile = 4;
    pipeline->next->cmds = cmd2;
    pipeline->next->next = NULL;

    run_pipeline(pipeline);

    // wait for all child processes to finish
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, 0)) != -1);

    free(pipeline->next);
    free(pipeline);

    return 0;
}
