#include "pipex.h"
// void pipeline(int ac,int *end,char **av,char **envp)
// {
//     int read_from;
//     int count;

//     read_from = dup(end[0]);
//     count = ac - 3;
//     while(count - 2)
//     {
//         close(end[0]);
//         close(end[1]);
//         pipe(end);
//         process_middle(ac,read_from,end,av[ac - count],envp);
//         close(read_from);
//         read_from = dup(end[0]);
//         count--;
//     }
//     close(read_from);
// }
// pid_t process_middle(int to_read,int *end, char *av, char **envp)
// {   
//     int pid;
//     char *holder;
//     char **cmd;
    
//     pid = fork();
//     if(pid == -1)
//         (close(end[0]),close(end[1]),close_std(),error_msg());
//     if(pid == 0)
//     {   
//         close(end[0]);
//         if(to_read == -1)
//             (close(end[1]),close_std(),error_msg());
//         cmd = ft_split(av,' ');
//         if(!cmd)
//             (close_std(), close(to_read),close(end[1]),error_msg());
//         holder = valid_path(cmd[0],envp);
//         if(!holder)
//             (close_std(), free_double(cmd), close(to_read),close(end[1]),error_msg());
//         execute(holder,cmd,end[1],to_read);
//         exit(EXIT_SUCCESS);
//     }
//     return(pid);
// }
int main(int ac,char **av, char **envp)
{   

    if(ac >= 5)
    {   
        t_pipex pipex;
        int end[2];
        int pid_one;
        int pid_two;
        int status;

        if(pipe(end) == -1)
            error_msg();
        pid_one = process_one(end,av,envp);
        // pipeline(ac,end,av,envp);
        pid_two = process_two(ac,end,av,envp);
        closing(end,-1);
        waitpid(pid_two,&status,0);
        waitpid(pid_one,&status,0);
        wait(NULL);
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