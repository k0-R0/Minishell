#include "header.h"

char *builtins[] = {
    "caller",   "true",    "type",   "hash",  "bind",   "help",    "dirs",
    "let",      "eval",    "set",    "unset", "export", "declare", "echo",
    "printf",   "read",    "cd",     "pwd",   "pushd",  "popd",    "typeset",
    "readonly", "getopts", "source", "exit",  "exec",   "shopt",   NULL};

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
        printf("%s\n", local_buffer);
        char *curr_cmd = malloc((strlen(local_buffer) + 1) * sizeof(char));
        strcpy(curr_cmd, local_buffer);
        cmdv[cmd_ind++] = curr_cmd;
    }
    for (int i = 0; i < cmd_ind; i++) {
        printf("%d -> %s\n", i, cmdv[i]);
    }
    return;
}

int main() {
    char *cmdv[200];
    extract_external_commands(cmdv);
}
