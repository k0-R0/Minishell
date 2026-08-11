#include "header.h"

int check_prompt_change(char *prompt, char *input_string) {
    if (strncmp(input_string, "PS1", 3) == 0) {
        if (input_string[3] == '=')
            return 0;
        else {
            printf("error in command\n");
            return 1;
        }
    }
    return 1;
}
void copy_change(char *prompt, char *input_string) {
    char local_buffer[100];
    strcpy(local_buffer, input_string + 4);
    sprintf(prompt, "%s%s %s>%s", ANSI_COLOR_BLUE, local_buffer,
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

void echo(char *input_string, int status);
