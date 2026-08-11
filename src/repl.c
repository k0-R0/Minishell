#include "header.h"

const char *builtins[] = {
    "bind",  "caller", "cd",     "declare", "dirs",    "echo",     "eval",
    "exec",  "exit",   "export", "getopts", "hash",    "help",     "let",
    "popd",  "printf", "pushd",  "pwd",     "read",    "readonly", "set",
    "shopt", "source", "true",   "type",    "typeset", "unset",    NULL};

const char *cmdv[160];
int cmd_count;

int check_command_type(char *command) {
    // check builtins
    printf("checking builtin\n");
    if (bin_search(builtins, sizeof(builtins) / sizeof(builtins[0]), command) ==
        1)
        return BUILTIN;
    printf("checking external\n");
    // check externals
    if (bin_search(cmdv, sizeof(cmdv) / sizeof(cmdv[0]), command) == 1)
        return EXTERNAL;
    // if none return non command
    return NO_COMMAND;
}

void scan_input(char *prompt, char *input_string) {
    extract_external_commands(cmdv, &cmd_count);
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
            char *command = get_command(input_string);
            printf("cmd -> %s\n", command);
            // check for internal, external or no command
            char command_type = check_command_type(command);
            printf("%d\n", command_type);
        }
    }
}
