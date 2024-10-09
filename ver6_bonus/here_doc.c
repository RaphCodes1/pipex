#include "pipex.h"

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
        cmd = ft_split(av[2],' ');
        if(!cmd)
            (close_std(), close(f1),close(end[1]),error_msg());
        holder = valid_path(cmd[0],envp);
        if(!holder)
            (close_std(), free_double(cmd), close(f1),close(end[1]),error_msg());
        execute(holder,cmd,end[1],f1);
        exit(EXIT_SUCCESS);
    }
    return(pid);
}