#include "pipex.h"
#include "get_next_line/get_next_line.h"

pid_t here_doc(int *end, char **av, char **envp)
{
    int pid;
    int f1;
    char *holder;
    char **cmd;
    
    pid = fork();
    if(pid == -1)
        (close(end[0]),close(end[1]),close_std(),error_msg());
    if(pid == 0)
    {
        close(end[0]);
        f1 = open("test",O_RDONLY);
        if(f1 == -1)
            (close(end[1]),close_std(),error_msg());
        if(dup2(f1,STDIN_FILENO) == -1)
            (close_std(),close(end[1]),close(f1),error_msg());
        if(dup2(end[1],STDOUT_FILENO) == -1)
            (close_std(),close(end[1]),close(f1),error_msg());
        exit(EXIT_SUCCESS);

    }
    return(pid);
}