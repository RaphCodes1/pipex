#include "pipex.h"

char **path_get(char **envp)
{
    int i;
    char **holder;
    i = 0;
    while(envp[i])
    {
        if(ft_strncmp(envp[i],"PATH=",5) == 0)
            holder = ft_split(envp[i] + 5,':');
        i++;
    }
    return(holder);
}

int valid_dir_ex(char *cmd)
{
    if(access(cmd,F_OK) != -1)
        return 1;
    return(0);
}
char *valid_path(char *cmd, char **envp)
{
    int i;
    char *holder_1;
    char *holder_2;
    char **cmd_paths;

    i = 0;
    cmd_paths = path_get(envp);
    if(!cmd_paths)
        return(NULL);
    if(valid_dir_ex(cmd) == 1)
        return (cmd);
    while(cmd_paths[i])
    {   
        holder_1 = ft_strjoin(cmd_paths[i],"/");
        holder_2 = ft_strjoin(holder_1,cmd);
        if(access(holder_2,F_OK) == -1)
            (free(holder_1),free(holder_2));
        else
        {
            free(holder_1);
            return (holder_2);
        }
        i++;
    }
    return (NULL);
}

