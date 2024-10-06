#include "pipex.h"

void error_msg(void)
{   
    // \033[31m
    perror("Error");
    exit(EXIT_FAILURE);
}

int av_count(char **av)
{
    int i;
    int f;

    i = 0;
    while(av[i] != NULL)
        i++;
    return (i);
}
void big_split(t_pipex *pipex, char **av)
{   
    int count = (av_count(av) - 1);
    char **holder;
    char ***s3 = ft_calloc((count + 1),sizeof(char **));
    if(!s3)
        error_msg();
    int i = 0;
    int start_av = 2;
    while(start_av < count)
    {   
        holder = ft_split(av[start_av],' ');
        s3[i] = holder;
        i++;
        start_av++;
    }
    s3[count] = NULL;
    pipex->cmd_args = s3;
}

void pipex_init(t_pipex *pipex, char **av, char **envp)
{   
    pipex->fd1 = open(av[1],O_RDONLY);
    pipex->fd2 = open(av[4],O_CREAT | O_RDWR | O_TRUNC, 0644);
    if(pipex->fd1 < 0 || pipex->fd2 < 0)
        error_msg();
    big_split(pipex, av);        
    path_get(pipex, envp);
    if(!pipex->cmd_paths)
    {
        free_everything(pipex);
        error_msg();
    }
}
