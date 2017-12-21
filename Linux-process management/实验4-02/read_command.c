#include "my_shell.h"


//return value: number of parameters
//0 represents only command without any parameters
//-1 represents wrong input
int read_command(char **command,char **parameters)
{
    char buffer[MAXLINE];
    fgets(buffer,MAXLINE,stdin);
    if(buffer[0] == '\0' || buffer[0] == '\n')
        return -1;
    char *pStart,*pEnd;
    int length = 0, count = 0,i;
    pStart = pEnd = buffer;
    while(*pEnd !='\0' && *pEnd != '\n')
    {
        while(*pEnd == ' ' && *pStart == ' ')
        {
            pStart++;
            pEnd++;
        }

        if(*pEnd == '\0' || *pEnd == '\n')
        {
            if(count == 0)
                return -1;
            break;
        }

        while(*pEnd != ' ' && *pEnd != '\0' && *pEnd != '\n')
            pEnd++;

        if(count == 0)
        {
            *command = malloc(sizeof(char)*(pEnd - pStart + 1));
            parameters[count] = malloc(sizeof(char)*(pEnd - pStart + 1));
            for(i=0;pStart<pEnd;i++,pStart++)
                (*command)[i] = *pStart;
                parameters[count][i] = *pStart;
            (*command)[i] = '\0';
            parameters[count][i] = '\0';
            count++;
            //printf("\ni:%d,command:  %s\n",i,*command);
        }
        else if(count <= MAXARG)
        {
            parameters[count] = malloc(sizeof(char)*(pEnd - pStart + 1));
            for(i=0;pStart<pEnd;i++,pStart++)
                parameters[count][i] = *pStart;
            parameters[count][i] = '\0';
            count++;
        }
        else
        {
            break;
        }
    }

    parameters[count] = NULL;

    /*input analysis
    printf("input analysis:\n");
    printf("command:%s\nparameters:\n",*command);
    for(i=1;i<count-1;i++)
        printf("%s\n",parameters[i]);*/
    return count;
}
