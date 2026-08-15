~~## external_command~~
- fork
- keep pid ,status(wait) global
- convert input string to a 2d array
- collect status

~~## internal_commmand~~
- pwd  :
    getcwd is the function to get current working directory
- cd   :
    chdir to change directory
- exit :
    exit(0) for exit
- echo()
    - echo $$ - print the minishell process id
    - echo $? - print the last status
    - echo $SHELL - print the env ; getenv()


## N pipe for external_command
~~- check pipe count~~
~~- if pipe count == 0 exec ~~
- else n pipe
    - test 
    - ~~for each pipe store NULL~~
    - ~~store cmd_ind in an array~~
    - take backup of stdin , stdout
    - ?? child doesn't continue the loop **IT DOES**
    - **UNDERSTAND HOW TO CLOSE AND OPEN MULTIPLE PIPES IN LOOP**
    - don't create pipe for the last child
    - don't do stuff with the pipe for the last child, it already has stdin and stdout setup

## Signals
writing your own handler is called "registering" a signal?
sa_flag = 0 -> sa_handler is called else the macro would be used and sa_sigaction is called
-   SIGINT in parent should just print prompt again
    -   keep prompt and input string in global
-   if external is running SIGINT should terminate the child(external)
-   SIGTSTP child process should take default behavior
    - jobs , fg , bg are all internal_commands
    -   jobs stack where fg and bg pop the last job
        - fg foreground execution of the child
        - bg background execution of the child wait nohang? (no user input programs)

- jobs structure
    - char *command
    - pid_t *pid
    - structure *pointer
    - stack using ll

- use WUNTRACED in the waitpid for child so that it returns when child is terminated as well as stopped

- delete node on completion - check status

- bg same as fg except it doesn't block parent

- parent handler will take backup of job ; inside handler if pid > 0

- update pid in child to 0 after execute_external_commands

- check SIGCHLD?


-----------------

## Resources to free

- command list 
- job list 
- 


## cleanup code 
- ~~pipe count and modification is repeated~~
- empty command not error
- ~~external commands binary search size to be fixed~~
