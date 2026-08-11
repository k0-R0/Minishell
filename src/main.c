#include "header.h"

int main() {
    char prompt[100];
    char input_string[100];
    sprintf(prompt, "%sMini$hell %s>%s", ANSI_COLOR_BLUE, ANSI_COLOR_YELLOW,
            ANSI_COLOR_RESET);
    scan_input(prompt, input_string);
}
