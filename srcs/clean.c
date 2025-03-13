/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:03:01 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/05 09:03:03 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	free_args(char **args)
{
	char	**ptr;

	ptr = args;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(args);
}

void	close_fds(t_pip *pip)
{
	if (pip->fd_out != -1)
		close(pip->fd_out);
	if (pip->fd_in != -1)
		close(pip->fd_in);
	if (pip->fd[0] != -1)
		close(pip->fd[0]);
	if (pip->fd[1] != -1)
		close(pip->fd[1]);
}

void	free_paths(t_pip *pip)
{
	int	i;

	i = -1;
	while (pip->paths[++i])
		free(pip->paths[i]);
	free(pip->paths);
}

void	clean_up(t_pip *pip)
{
	if (pip->cmd1_args)
		free_args(pip->cmd1_args);
	if (pip->cmd2_args)
		free_args(pip->cmd2_args);
	if (pip->cmd1_path)
		free(pip->cmd1_path);
	if (pip->cmd2_path)
		free(pip->cmd2_path);
	if (pip->paths)
		free_paths(pip);
	close_fds(pip);
}

void	clean_exit(t_pip *pip)
{
	clean_up(pip);
	exit (1);
}
