#include "pipex.h"
#include "get_next_line/get_next_line.h"

char *get_lines(char *stopper)
{
    char *joined_str;
    char *next_line;
    char *temp;

    joined_str = ft_strdup("");
    next_line = get_next_line(STDIN_FILENO);
    if(!next_line)
    {
        (free(next_line),free(joined_str));
        return(NULL);
    }
    while(next_line)
    {   
        if(ft_strncmp(next_line,stopper,(ft_strlen(stopper) + 1)) == 0)
        {
            free(next_line);
            return(joined_str);
        }
        temp = ft_strjoin(joined_str,next_line);
        free(joined_str);
        joined_str = temp;
        free(next_line);
        next_line = get_next_line(STDIN_FILENO);
    }
    return(NULL);
}
pid_t here_doc(int *end, char **av)
{
    int pid;
    char *next_line;
    char *stopper;

    stopper = ft_strjoin(av[2],"\n");
    next_line = get_lines(stopper);
    if(!next_line)
        (close(end[1]),close(end[0]),error_msg());
    pid = fork();
    if(pid == -1)
        (close(end[0]),close(end[1]),close_std(),error_msg());
    if(pid == 0)
    {   
        close(end[0]);
        if(dup2(end[1],STDOUT_FILENO) == -1)
            (close_std(),close(end[1]),error_msg());
        write(end[1],next_line,ft_strlen(next_line));
        (free(next_line),free(stopper));
        exit(EXIT_SUCCESS);
    }
    (free(stopper),free(next_line));
    return(pid);
}
