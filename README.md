## empty command not error

## external_command
- fork
- keep pid ,status(wait) global
- convert input string to a 2d array
- collect status

## internal_commmand
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
- check pipe count
- if pipe count == 0 exec 
- else n pipe
