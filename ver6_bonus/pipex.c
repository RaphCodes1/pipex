#include "pipex.h"

void wait_for_processs(int ac)
{
    int i;

    i = 2;
    while(i < (ac - 2))
    {
        wait(NULL);
        i++;
    }
}
int main(int ac,char **av, char **envp)
{   
    if(ac == 5)
    {   
        int end[2];
        int pid_two;
        int pid_one;
        int status;

        if(pipe(end) == -1)
            error_msg();
        pid_one = process_one(end,av,envp);
        pid_two = process_two(ac,end,av,envp);
        closing(end,-1);
        waitpid(pid_one,&status,0);
        waitpid(pid_two,&status,0);
        wait_for_processs(ac);
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