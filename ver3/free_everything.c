#include "pipex.h"

void free_everything(t_pipex *pipex)
{   
    int i;
    int f;

    i = 0;
    while(pipex->cmd_args[i] != NULL)
    {
        f = 0;
        while(pipex->cmd_args[i][f])
        {
            free(pipex->cmd_args[i][f]);
            f++;
        }
        free(pipex->cmd_args[i]);
        i++;
    }
    free(pipex->cmd_args);
    i = 0;
    while(pipex->cmd_paths[i] != NULL)
    {
        free(pipex->cmd_paths[i]);
        i++;
    }
    free(pipex->cmd_paths);
}

void free_cmd_double(char **holder)
{   
    int i;

    i = 0;
    while(holder[i] != NULL)
    {
        free(holder[i]);
        i++;
    }
    free(holder);
}