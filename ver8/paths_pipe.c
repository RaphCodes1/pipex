/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:57:19 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/14 20:01:12 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_get(char **envp)
{
	int		i;
	char	**holder;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			holder = ft_split(envp[i] + 5, ':');
			return (holder);
		}
		i++;
	}
	return (NULL);
}

int	valid_dir_ex(char *cmd)
{
	if (access(cmd, F_OK) != -1)
		return (1);
	return (0);
}

char	*valid_path(char *cmd, char **envp)
{
	int		i;
	char	*holder_1;
	char	*holder_2;
	char	**cmd_paths;

	i = 0;
	if (valid_dir_ex(cmd) == 1)
		return (cmd);
	cmd_paths = path_get(envp);
	if (!cmd_paths)
		return (NULL);
	while (cmd_paths[++i])
	{
		holder_1 = ft_strjoin(cmd_paths[i], "/");
		holder_2 = ft_strjoin(holder_1, cmd);
		if (access(holder_2, F_OK) == -1)
			(free(holder_1), free(holder_2));
		else
		{
			(free(holder_1), free_double(cmd_paths));
			return (holder_2);
		}
	}
	free_double(cmd_paths);
	return (NULL);
}
