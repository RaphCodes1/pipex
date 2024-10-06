NAME = pipex
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c utils.c paths_pipe.c free_everything.c libft/ft_putstr_fd.c libft/ft_split.c \
		libft/ft_strlcpy.c libft/ft_strncmp.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_calloc.c \
		libft/ft_bzero.c

OBJS = $(SRCS:.c=.o)

all:$(NAME)

#add CFLAGS Later
$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) -c $^ -o $@

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus