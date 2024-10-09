NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c utils.c paths_pipe.c execute_pipes.c libft/ft_putstr_fd.c libft/ft_split.c \
		libft/ft_strlcpy.c libft/ft_strncmp.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_calloc.c \
		libft/ft_bzero.c

SRCS_BONUS = pipex_bonus.c utils.c paths_pipe.c execute_pipes.c libft/ft_putstr_fd.c libft/ft_split.c \
		libft/ft_strlcpy.c libft/ft_strncmp.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_calloc.c \
		libft/ft_bzero.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)
bonus: $(NAME) $(NAME_BONUS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) -c $^ -o $@

clean: 
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus