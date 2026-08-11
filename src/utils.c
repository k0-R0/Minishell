#include "header.h"

void extract_external_commands(char **cmdv) {
    FILE *fptr = fopen("external_commands.txt", "r");
    if (fptr == NULL) {
        printf("Unable to open file\n");
        return;
    }
    int cmd_ind = 0;
    char ch;
    while (feof(fptr) == 0) {
        char local_buffer[100];
        if (fgets(local_buffer, 100, fptr) == NULL)
            break;
        char *curr_cmd = malloc((strlen(local_buffer) + 1) * sizeof(char));
        strcpy(curr_cmd, local_buffer);
        cmdv[cmd_ind++] = curr_cmd;
    }
    // for (int i = 0; i < cmd_ind; i++) {
    //     printf("%d -> %s\n", i, cmdv[i]);
    // }
    return;
}

static int check_prompt_change(char *prompt, char *input_string) {
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

void scan_input(char *prompt, char *input_string) {
    char *cmdv[200];
    extract_external_commands(cmdv);
    while (1) {
        printf("\n%s", prompt);
        // check if it is PS1
        // if it is copy_change prompt
        fgets(input_string, 100, stdin);
        input_string[strcspn(input_string, "\n")] = '\0';
        if (check_prompt_change(prompt, input_string) == 0) {
            copy_change(prompt, input_string);
        }
        // if not get command
        else {
            char *cmd = get_command(input_string);
            printf("cmd -> %s", cmd);
        }
        // check for internal, external or no command
    }
}

void copy_change(char *prompt, char *input_string);

int check_command_type(char *command);
void echo(char *input_string, int status);
