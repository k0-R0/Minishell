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

// job handler structure
typedef struct job {
    int pid;
    char *process_name;
    struct job *next;
} job;

extern job *g_job_list;
extern char prompt[100];
extern char input_string[100];
extern int status;
extern pid_t child_pid;
// default prompt is minishell
void scan_input(char *prompt, char *input_string);

void extract_external_commands(const char *external_commands[], int *cmd_count);
// check for prompt update before using get_command
// use strncmp
char *get_command(char *input_string);

// validate then update prompt
// error = "command not found"
void copy_change(char *prompt, char *input_string);

int check_command_type(char *command);
int check_prompt_change(char *prompt, char *input_string);
void echo(char *input_string);
void execute_internal_commands(char *input_string);
void execute_external_commands(char *input_string);
void signal_handler(int sig_num);
char bin_search(const char *const argv[], int size, const char *target);
void getwords(char *tokens[], const char *const input_string);
void get_pipe_count(char *tokens[], int *pipe_count);

int insert_job(int pid, char *process_name, job **head);
void print_jobs(job *head);
void remove_job(job **head);

#endif
