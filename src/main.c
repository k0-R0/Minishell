#include "header.h"

char *builtins[] = {
    "caller",   "true",    "type",   "hash",  "bind",   "help",    "dirs",
    "let",      "eval",    "set",    "unset", "export", "declare", "echo",
    "printf",   "read",    "cd",     "pwd",   "pushd",  "popd",    "typeset",
    "readonly", "getopts", "source", "exit",  "exec",   "shopt",   NULL};

int main() {
    char prompt[100];
    char input_string[100];
    sprintf(prompt, "%sMini$hell %s>%s", ANSI_COLOR_BLUE, ANSI_COLOR_YELLOW,
            ANSI_COLOR_RESET);
    scan_input(prompt, input_string);
}
