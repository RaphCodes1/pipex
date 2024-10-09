#include "pipex.h"

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
        pid_one = process_one(end,av,envp);
        pid_two = process_two(ac,end,av,envp);
        closing(end,-1);
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