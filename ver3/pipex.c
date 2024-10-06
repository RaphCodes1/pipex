#include "pipex.h"

void closing(int *end, t_pipex *pipex)
{
    if (end[0] != -1)
        close(end[0]);
    if (end[1] != -1)
        close(end[1]);
    if (pipex->fd1 != -1)
        close(pipex->fd1);
    if (pipex->fd2 != -1)
        close(pipex->fd2);
}

void p_err(t_pipex *pipex, int *end)
{   
    closing(end,pipex);
    free_everything(pipex);
    error_msg();
}
pid_t process_one(int f1,int *end, char **cmd1, t_pipex *pipex)
{   
    int pid;
    char *holder;
    
    pid = fork();
    if(pid == -1)
        error_msg();
    if(pid == 0)
    {   
        if(dup2(f1,STDIN_FILENO) == -1)
            p_err(pipex,end);
        if(dup2(end[1],STDOUT_FILENO) == -1)
            p_err(pipex,end);
        closing(end,pipex);
        holder = valid_path(cmd1[0], pipex);
        if(!holder)
            (close(0), close(1),p_err(pipex,end));
        if(execve(holder, cmd1, NULL) == -1)
            (close(0), close(1),p_err(pipex,end),free(holder));
        free(holder);
        exit(EXIT_SUCCESS);
    }
    return(pid);
}

pid_t process_two(int f2, int *end, char **cmd2, t_pipex *pipex)
{   
    int pid;
    char *holder;
    
    pid = fork();
    if(pid == -1)
        error_msg();
    if(pid == 0)
    {   
        if(dup2(f2, STDOUT_FILENO) == -1)
            p_err(pipex,end);
        if(dup2(end[0],STDIN_FILENO) == -1)
            p_err(pipex,end);
        closing(end,pipex);
        holder = valid_path(cmd2[0],pipex);
        if(!holder)
            (close(0), close(1), p_err(pipex,end));
        if(execve(holder, cmd2, NULL) == -1)
            (close(0), close(1),p_err(pipex,end),free(holder));
        free(holder);
        exit(EXIT_SUCCESS);
    }
    return(pid);
}

int main(int ac,char **av, char **envp)
{   
    if(ac == 5)
    {   
        t_pipex pipex;
        int end[2];
        int pid_one;
        int pid_two;
        int status;

        if(pipe(end) == -1)
            error_msg();
        pipex_init(&pipex, av, envp);
        pid_one = process_one(pipex.fd1,end,pipex.cmd_args[0],&pipex);
        pid_two = process_two(pipex.fd2,end,pipex.cmd_args[1],&pipex);
        closing(end,&pipex);
        free_everything(&pipex);
        waitpid(pid_one,&status,0);
        waitpid(pid_two,&status,0);
        if(WIFEXITED(status))
            return(WEXITSTATUS(status));
        else if(WIFSIGNALED(status))
            return(WTERMSIG(status));
        exit(EXIT_SUCCESS);
    }
    else
        putstr_fd("\033[31mEnter Valid Input: \033[0m<file1> <cmd1> <cmd2> <file2>\n",1);
    return(0);
}



