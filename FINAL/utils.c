/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:57:40 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/14 20:06:49 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	closing(int *end, int fd)
{
	if (end[0] != -1)
		close(end[0]);
	if (end[1] != -1)
		close(end[1]);
	if (fd != -1)
		close(fd);
}

void	free_double(char **holder)
{
	int	i;

	i = 0;
	while (holder[i] != NULL)
	{
		free(holder[i]);
		i++;
	}
	free(holder);
}

void	close_std(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
