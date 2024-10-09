#include "pipex.h"


void execute(char *holder, char **cmd, int write, int read)
{   
    if(dup2(read,STDIN_FILENO) == -1)
    {
        (close_std(), free(holder), free_double(cmd), 
        close(read),close(write));
    }
    if(dup2(write,STDOUT_FILENO) == -1)
    {
        (close_std(), free(holder), free_double(cmd), 
        close(read),close(write));
    }
    if(execve(holder, cmd, NULL) == -1)
    {
        (close_std(), free(holder), free_double(cmd), 
        close(read),close(write));
    }
}

pid_t process_one(int *end, char **av, char **envp)
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
        f1 = open(av[1],O_RDONLY);
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

pid_t process_two(int ac, int *end, char **av, char **envp)
{   
    int pid;
    int f2;
    char *holder;
    char **cmd;
    
    pid = fork();
    if(pid == -1)
        (close(end[0]),close(end[1]),close_std(),error_msg());
    if(pid == 0)
    {   
        close(end[1]);
        f2 = open(av[ac - 1],O_CREAT | O_RDWR | O_TRUNC, 0644);
        if(f2 == -1)
            (close(end[0]),close_std(),error_msg());
        cmd = ft_split(av[ac - 2],' ');
        if(!cmd)
            (close(end[0]),close_std(),error_msg());
        holder = valid_path(cmd[0],envp);
        if(!holder)
            (close_std(), free_double(cmd),close(f2),close(end[1]),error_msg());
        execute(holder,cmd,f2,end[0]);
        exit(EXIT_SUCCESS);
    }
    return(pid);
}