#include "header.h"

char *builtins[] = {
    "caller",   "true",    "type",   "hash",  "bind",   "help",    "dirs",
    "let",      "eval",    "set",    "unset", "export", "declare", "echo",
    "printf",   "read",    "cd",     "pwd",   "pushd",  "popd",    "typeset",
    "readonly", "getopts", "source", "exit",  "exec",   "shopt",   NULL};

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
            // check for internal, external or no command
        }
    }
}
