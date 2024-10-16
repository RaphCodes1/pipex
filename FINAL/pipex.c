/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:57:24 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/14 20:06:01 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_processs(int ac)
{
	int	i;

	i = 2;
	while (i < (ac - 2))
	{
		wait(NULL);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	int	end[2];
	int	pid_two;
	int	pid_one;
	int	status;

	if (ac == 5)
	{
		if (pipe(end) == -1)
			error_msg();
		pid_one = process_one(end, av, envp);
		pid_two = process_two(ac, end, av, envp);
		closing(end, -1);
		waitpid(pid_one, &status, 0);
		waitpid(pid_two, &status, 0);
		wait_for_processs(ac);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status));
		exit(EXIT_SUCCESS);
	}
	else
		putstr_fd("\033[31mEnter Valid Input\n", 1);
	return (0);
}
