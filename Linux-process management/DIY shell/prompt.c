#include <pwd.h>
#include "my_shell.h"
const int max_name_len = 256;
const int max_path_len = 1024;

void prompt()
{
    struct passwd *pwd;
    char hostname[max_name_len];
    char pathname[max_path_len];
    pwd = getpwuid(getuid()); // get username and home path
    getcwd(pathname,max_path_len); // get now path
    printf("[GROUP1]%s@unbuntu:",pwd->pw_name);

    if(strlen(pathname) < strlen(pwd->pw_dir) || 
            strncmp(pathname,pwd->pw_dir,strlen(pwd->pw_dir))!=0)
        printf("%s$ ",pathname);
    else
        printf("~%s$ ",pathname+strlen(pwd->pw_dir));
    return;
}
