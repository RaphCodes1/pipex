#include "pipex.h"
#include "get_next_line/get_next_line.h"

int main(int ac, char **av)
{   
    int pipefd[2];
    pid_t pid;
    int fd2 = open("outfile_here",O_CREAT | O_RDWR | O_APPEND, 0644);
    char *joined_str;
    char *next_line;
    char *stopper;
    int i = 0;
    stopper = ft_strjoin(av[2],"\n");
    joined_str = "";
    next_line = get_next_line(STDIN_FILENO);
    while(next_line)
    {
        if(ft_strncmp(next_line,stopper,(ft_strlen(stopper) + 1)) == 0)
            break;
        joined_str = ft_strjoin(joined_str,next_line);
        free(next_line);
        next_line = get_next_line(STDIN_FILENO);
    }
    // printf("%s",joined_str);
    if(pipe(pipefd) == -1)
        return 1;
    pid = fork();
    if(pid == -1)
        exit(EXIT_FAILURE);
    if(pid == 0)
    {  
       int checker = write(fd2,joined_str,ft_strlen(joined_str));
       if(!checker)
       {
            perror("error");
            close(fd2);
       }
    }
    
}