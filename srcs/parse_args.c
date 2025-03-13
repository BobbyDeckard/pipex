/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:38:23 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/05 19:38:29 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

static void	parse_outfile(t_pip *pip, const char *file2)
{
	if (access(file2, F_OK) == 0 && access(file2, W_OK))
		perror(file2);
	else
		pip->fd_out = open(file2, O_TRUNC | O_WRONLY | O_CREAT, 0644);
}

static void	parse_infile(t_pip *pip, const char *file1)
{
	if (access(file1, F_OK) || access(file1, R_OK))
		perror(file1);
	else
		pip->fd_in = open(file1, O_RDONLY);
}

static void	parse_cmd(t_pip *pip, char ***pip_cmd, const char *cmd)
{
	*pip_cmd = ft_split(cmd, ' ');
	if (!*pip_cmd)
		clean_exit(pip);
}

void	parse_args(t_pip *pip, char **av)
{
	parse_infile(pip, av[1]);
	parse_outfile(pip, av[4]);
	parse_cmd(pip, &pip->cmd1_args, av[2]);
	parse_cmd(pip, &pip->cmd2_args, av[3]);
}
