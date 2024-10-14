/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:57:10 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/14 20:00:31 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *holder, char **cmd, int write, int read)
{
	if (dup2(read, STDIN_FILENO) == -1)
	{
		(close_std(), free(holder), free_double(cmd), close(read), close(write),
			error_msg());
	}
	close(read);
	if (dup2(write, STDOUT_FILENO) == -1)
	{
		(close_std(), free(holder), free_double(cmd), close(read), close(write),
			error_msg());
	}
	close(write);
	execve(holder, cmd, NULL);
	(close_std(), free_double(cmd), error_msg());
}

pid_t	process_one(int *end, char **av, char **envp)
{
	int		pid;
	int		f1;
	char	*holder;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		(close(end[0]), close(end[1]), close_std(), error_msg());
	if (pid == 0)
	{
		close(end[0]);
		f1 = open(av[1], O_RDONLY);
		if (f1 == -1)
			(close(end[1]), close_std(), error_msg());
		cmd = ft_split(av[2], ' ');
		if (!cmd || cmd[0] == NULL)
			(close_std(), close(f1), close(end[1]), free(cmd), error_msg());
		holder = valid_path(cmd[0], envp);
		if (!holder)
			(close_std(), free_double(cmd), close(f1), close(end[1]),
				close(end[0]), error_msg());
		execute(holder, cmd, end[1], f1);
	}
	return (pid);
}

pid_t	process_two(int ac, int *end, char **av, char **envp)
{
	int		pid;
	int		f2;
	char	*holder;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		(close(end[0]), close(end[1]), close_std(), error_msg());
	if (pid == 0)
	{
		close(end[1]);
		f2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (f2 == -1)
			(close(end[0]), close_std(), error_msg());
		cmd = ft_split(av[ac - 2], ' ');
		if (!cmd || cmd[0] == NULL)
			(close(end[0]), close_std(), close(f2), free(cmd), error_msg());
		holder = valid_path(cmd[0], envp);
		if (!holder)
			(close_std(), free_double(cmd), close(f2), close(end[1]),
				close(end[0]), error_msg());
		execute(holder, cmd, f2, end[0]);
	}
	return (pid);
}

void	multiple_pipes(int ac, int *end, char **av, char **envp)
{
	int	read_from;
	int	count;

	read_from = dup(end[0]);
	count = ac - 3;
	while (count - 2)
	{
		close(end[0]);
		close(end[1]);
		pipe(end);
		process_middle(read_from, end, av[ac - count], envp);
		close(read_from);
		read_from = dup(end[0]);
		count--;
	}
	close(read_from);
}

pid_t	process_middle(int to_read, int *end, char *av, char **envp)
{
	int		pid;
	char	*holder;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		(close(end[0]), close(end[1]), close_std(), error_msg());
	if (pid == 0)
	{
		close(end[0]);
		if (to_read == -1)
			(close(end[1]), close_std(), error_msg());
		cmd = ft_split(av, ' ');
		if (!cmd || cmd[0] == NULL)
			(close_std(), close(to_read), close(end[1]), free(cmd),
				error_msg());
		holder = valid_path(cmd[0], envp);
		if (!holder)
			(close_std(), free_double(cmd), close(to_read), close(end[1]),
				error_msg());
		execute(holder, cmd, end[1], to_read);
	}
	return (pid);
}
