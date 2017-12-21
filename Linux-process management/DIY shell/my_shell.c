#include "my_shell.h"
#define TRUE 1

void proc(void)
{
    int status,i;
    char *command;
    char **parameters;
    parameters = malloc(sizeof(char *)*(MAXARG+2));
    while(TRUE)
    {
        prompt();
        if(-1 == read_command(&command,parameters)){
            continue;
        }
        if(strcmp(command,"exit")==0)
            exit(0);
        if(fork()!=0)
        {
            waitpid(-1,&status,0); // stop parent
        }
        else {
            if(strcmp(command, "cmd1") == 0 ||
               strcmp(command, "cmd2") == 0 ||
               strcmp(command, "cmd3") == 0) {
                char num = command[3];
                strcpy(command, "./cmd");
                command[5] = num;
                command[6] = '\0'; 
                strcmp(parameters[0], command);  
            }

            if(execvp(command, parameters) == -1){
                printf("Command not found\n");
            }
            exit(0);
        }
    }
}

int main() {
    proc();
    return 0;
}
