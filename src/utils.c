#include "header.h"

void extract_external_commands(const char *cmdv[], int *cmd_count) {
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
        local_buffer[strcspn(local_buffer, "\n")] = '\0';
        char *curr_cmd = malloc((strlen(local_buffer) + 1) * sizeof(char));
        strcpy(curr_cmd, local_buffer);
        cmdv[cmd_ind++] = curr_cmd;
    }
    *cmd_count = cmd_ind;
    return;
}

char bin_search(const char *const argv[], int size, const char *target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(argv[mid], target);
        if (cmp == 0)
            return 1;
        else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0;
}
