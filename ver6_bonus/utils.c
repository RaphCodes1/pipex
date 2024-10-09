#include "pipex.h"

void error_msg(void)
{   
    perror("Error");
    exit(EXIT_FAILURE);
}

void closing(int *end, int fd)
{
    if (end[0] != -1)
        close(end[0]);
    if (end[1] != -1)
        close(end[1]);
    if (fd != -1)
        close(fd);
}

void p_err(int *end, int fd)
{   
    closing(end,fd);
    error_msg();
}

void free_double(char **holder)
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

