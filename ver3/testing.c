#include "pipex.h"
#include <string.h>

int av_count(char **av)
{
    int i;
    int f;

    i = 0;
    while(av[i])
    {
        i++;
    }
    return (i);
}
pid_t process_one()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        printf("error");
        exit(EXIT_FAILURE);
    }
    if(pid == 0)
    {
        printf("child process one\n");
        exit(EXIT_SUCCESS);
    }
    return(pid);
}

pid_t process_two()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        printf("error");
        exit(EXIT_FAILURE);
    }
    if(pid == 0)
    {
        printf("child process two\n");
        sleep(2);
        printf("testing for TWO\n");
        exit(EXIT_SUCCESS);
    }
    return(pid);
}

// void pipex_cmd(t_pipex *pipex)
// {
//     int end[2];
//     pid_t pid;

//     if(pipe(end) == -1)
//         error_msg();
//     pid = fork();
//     if(pid < 0)
//         error_msg();
//     if(pid == 0)
//     {
//         child_process(pipex->fd1, end, pipex->cmd_args[0],pipex);
//     }
//     else
//     {
//         parent_process(pipex->fd2, end, pipex->cmd_args[1], pipex);
//     }
// }

int main(int ac, char **av, char **envp)
{
    int end[2];
    int pid_one;
    int pid_two;
    int status;

    pid_one = process_one();
    pid_two = process_two();
    if(waitpid(pid_one,&status,0) == -1)
    {
        printf("error 1");
        exit(EXIT_FAILURE);
    }
    if(waitpid(pid_two,&status,0) == -1)
    {
        printf("error 2");
        exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)) {
        printf("Child process (PID1: %d PID2: %d) exited with status %d\n",pid_one, pid_two, WEXITSTATUS(status));
    } else {
        printf("Child process did not terminate normally\n");
    }

    printf("Parent process (PID: %d) exiting.\n", getpid());
    return 0;
    
    
       
   
    
    
    
    
}