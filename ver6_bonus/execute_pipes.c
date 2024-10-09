#include "pipex.h"

void execute(char *holder, char **cmd, int *end, int fd)
{
    if(execve(holder, cmd, NULL) == -1)
    {
        (close(0), close(1), free(holder), free_double(cmd), 
        p_err(end,fd));
    }
}

void in_and_out(int fd,int out,int proc,int *end)
{   
    if(proc == 1)
    {
        dup2(fd, STDIN_FILENO);
        dup2(out,STDOUT_FILENO);
    }
    else if(proc == 2)
    {
        dup2(out, STDIN_FILENO);
        dup2(fd,STDOUT_FILENO);
    }
    closing(end,fd);
}
pid_t process_one(int *end, char **av, char **envp)
{   
    int pid;
    int f1;
    char *holder;
    char **cmd;
    
    pid = fork();
    if(pid == -1)
        error_msg();
    if(pid == 0)
    {   
        f1 = open(av[1],O_RDONLY);
        if(f1 == -1)
            p_err(end,f1);
        in_and_out(f1,end[1],1,end);
        cmd = ft_split(av[2],' ');
        if(!cmd)
            (close(0), close(1), p_err(end,f1));
        holder = valid_path(cmd[0],envp);
        if(!holder)
            (close(0), close(1), free_double(cmd), p_err(end,f1));
        execute(holder,cmd,end,f1);
        (free(holder),free_double(cmd),exit(EXIT_SUCCESS));
    }
    return(pid);
}

pid_t process_two(int *end, char **av, char **envp)
{   
    int pid;
    int f2;
    char *holder;
    char **cmd;
    
    pid = fork();
    if(pid == -1)
        error_msg();
    if(pid == 0)
    {   
        f2 = open(av[4],O_CREAT | O_RDWR | O_TRUNC, 0644);
        if(f2 == -1)
            p_err(end,f2);
        in_and_out(f2,end[0],2,end);
        cmd = ft_split(av[3],' ');
        if(!cmd)
            (close(0), close(1), p_err(end,f2));
        holder = valid_path(cmd[0],envp);
        if(!holder)
            (close(0), close(1), free_double(cmd), p_err(end,f2));
        execute(holder,cmd,end,f2);
        (free(holder),free_double(cmd),exit(EXIT_SUCCESS));
    }
    return(pid);
}