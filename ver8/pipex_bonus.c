/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:57:21 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/14 20:08:15 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
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
	int	status;

	if (ac >= 5)
	{
		if (pipe(end) == -1)
			error_msg();
		if (ft_strncmp(av[1], "here_doc", 9) == 0)
		{
			if (ac >= 6)
				here_doc(end, av);
			else
			{
				(close(end[1]), close(end[0]));
				return (EXIT_FAILURE);
			}
		}
		else
			process_one(end, av, envp);
		multiple_pipes(ac, end, av, envp);
		pid_two = process_two(ac, end, av, envp);
		closing(end, -1);
		waitpid(pid_two, &status, 0);
		wait_for_processs(ac);
		return (WEXITSTATUS(status));
	}
	else
		putstr_fd("\033[31mEnter Valid Input\n", 1);
	return (0);
}
