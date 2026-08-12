#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int status;

int check_prompt_change(char *prompt, char *input_string) {
    if (strlen(input_string) > 4 && strncmp(input_string, "PS1", 3) == 0) {
        if (input_string[3] == '=' && input_string[4] != ' ')
            return 0;
        else
            printf("%serror in command\n%s", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    }
    return 1;
}
void copy_change(char *prompt, char *input_string) {
    char local_buffer[100];
    sprintf(local_buffer, "%s", input_string + 4);
    local_buffer[strcspn(local_buffer, " ")] = '\0';
    sprintf(prompt, "%s%s%s> %s", ANSI_COLOR_BLUE, local_buffer,
            ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
}

char *get_command(char *input_string) {
    char local_buffer[100];
    int char_count = strcspn(input_string, " \n");
    strncpy(local_buffer, input_string, char_count);
    local_buffer[char_count] = '\0';
    char *cmd = malloc((strlen(local_buffer) + 1) * sizeof(char));
    strcpy(cmd, local_buffer);
    return cmd;
}

void execute_internal_commands(char *input_string) {
    if (strcmp(input_string, "pwd") == 0) {
        char directory[200];
        getcwd(directory, sizeof(directory));
        printf("%s", directory);
    } else if (strncmp(input_string, "cd", 2) == 0 &&
               (input_string[2] == ' ' || input_string[2] == '\t')) {
        // strlen("cd ") is 3
        int path_ind = strspn(input_string + 3, " \t") + 3;
        if (chdir(input_string + path_ind) == -1) {
            perror(NULL);
            return;
        }
    } else if (strcmp(input_string, "exit") == 0) {
        exit(0);
    } else if (strncmp(input_string, "echo ", 5) == 0) {
        echo(input_string);
    } else {
        printf("%sCommand not found%s", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    }
}

void echo(char *input_string) {
    char *arg = input_string + 5;
    if (strcmp(arg, "$$") == 0) {
        printf("Process id -> %d", getpid());
    } else if (strcmp(arg, "$?") == 0) {
        printf("Exit status -> %d", WEXITSTATUS(status));
    } else if (strcmp(arg, "$SHELL") == 0) {
        printf("%s", getenv("SHELL"));
    } else {
        printf("%sInvalid argument%s", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    }
}

void execute_external_commands(char *input_string) {
    char *tokens[100];
    getwords(tokens, input_string);
    int pipe_count = 0;
    get_pipe_count(tokens, &pipe_count);
    if (pipe_count == 0) {
        if (execvp(tokens[0], tokens) == -1) {
            perror(NULL);
        }
    } else {
        printf("%sInvalid argument%s", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    }
}
