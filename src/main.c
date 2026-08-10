#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUILTIN 1
#define EXTERNAL 2
#define NO_COMMAND 3

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);

void copy_change(char *prompt, char *input_string);

int check_command_type(char *command);
void echo(char *input_string, int status);
void execute_internal_commands(char *input_string);
void signal_handler(int sig_num);
void extract_external_commands(char **external_commands);

int read_external_cmd(const char *path, char *cmdv[]) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror(NULL);
        return 1;
    }
    int cmd_ind = 0;
    char ch;
    while (read(fd, &ch, 1) > 0) {
        char *curr_cmd = malloc(100 * sizeof(char));
        int ind = 0;
        curr_cmd[ind++] = ch;
        while (ch != '\n') {
            if (read(fd, &ch, 1) > 0)
                curr_cmd[ind++] = ch;
        }
        curr_cmd[ind] = '\0';
        cmdv[cmd_ind++] = curr_cmd;
    }
    for (int i = 0; i < cmd_ind; i++) {
        printf("%s\n", cmdv[i]);
    }
    return 0;
}

int main() {
    char *cmdv[200];
    if (read_external_cmd("external_commands.txt", cmdv)) {
        printf("error reading file\n");
        return 1;
    }
}

#endif
