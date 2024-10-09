#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>


//libft
void	putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);

void    error_msg(void);
void    free_double(char **holder);
void    closing(int *end, int fd);
void    close_std(void);

pid_t process_one(int *end, char **av, char **envp);
pid_t process_two(int ac, int *end, char **av, char **envp);
pid_t process_middle(int to_read,int *end, char *av, char **envp);
void multiple_pipes(int ac,int *end,char **av,char **envp);
void execute(char *holder, char **cmd, int write, int read);

char    **path_get(char **envp);
char    *valid_path(char *cmd, char **envp);

pid_t here_doc(int *end, char **av, char **envp);