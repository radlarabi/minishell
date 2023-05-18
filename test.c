#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

int exitFlag = 0;

void handleSignal(int signal) {
    if (signal == SIGINT) {
        printf("End of input.\n");
        exitFlag = 1;
    }
}

int main() {
    signal(SIGINT, handleSignal);

    printf("Enter text (Ctrl+D to exit):\n");

    char *line;

    while (!exitFlag && (line = readline(NULL))) {
        if (line[0] == '\0') {
            printf("End of input.\n");
            break;
        }

        add_history(line);
        printf("Entered text: %s\n", line);
        free(line);
    }

    return 0;
}
