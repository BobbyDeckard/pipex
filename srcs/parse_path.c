/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:38:34 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/05 19:40:11 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

static void	found_path(t_pip *pip, char **pip_path, char *path)
{
	*pip_path = ft_strdup(path);
	free(path);
	if (!*pip_path)
	{
		perror("malloc");
		clean_exit(pip);
	}
}

static void	get_cmd_path(t_pip *pip, char **pip_path, char *cmd)
{
	char	*path;
	int		i;

	i = -1;
	while (pip->paths[++i])
	{
		path = ft_strjoin(pip->paths[i], cmd);
		if (access(path, F_OK) == 0)
			return (found_path(pip, pip_path, path));
		free(path);
	}
	ft_printf("pipex: %s: command not found\n", cmd);
}

void	parse_paths(t_pip *pip, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			break ;
	}
	envp[i] += 5;
	pip->paths = ft_split_path(envp[i], ':');
	get_cmd_path(pip, &pip->cmd1_path, pip->cmd1_args[0]);
	get_cmd_path(pip, &pip->cmd2_path, pip->cmd2_args[0]);
}
