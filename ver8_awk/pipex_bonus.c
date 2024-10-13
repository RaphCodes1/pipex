#include "pipex.h"
#include "get_next_line/get_next_line.h"

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
    if(ac >= 5)
    {   
        int end[2];
        int pid_two;
        int status;

        if(pipe(end) == -1)
            error_msg();
        if(ft_strncmp(av[1],"here_doc",9) == 0)
            if(ac >= 6)
                here_doc(end,av);
            else
            {
                (close(end[1]),close(end[0]));
                return(EXIT_FAILURE);
            }
        else
            process_one(end,av,envp);
        multiple_pipes(ac,end,av,envp);
        pid_two = process_two(ac,end,av,envp);
        closing(end,-1);
        waitpid(pid_two,&status,0);
        wait_for_processs(ac);
        return(WEXITSTATUS(status));
    }
    else
        putstr_fd("\033[31mEnter Valid Input: \033[0m<file1> <cmd1> <cmd2> ..... <file2>\n",1);
    return(0);
}