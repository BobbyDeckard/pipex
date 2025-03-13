/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:02:43 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/05 09:02:44 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

static t_pip	init_struct(void)
{
	t_pip	pip;

	if (pipe(pip.fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	pip.cmd1_args = NULL;
	pip.cmd2_args = NULL;
	pip.cmd1_path = NULL;
	pip.cmd2_path = NULL;
	pip.paths = NULL;
	pip.fd_out = -1;
	pip.fd_in = -1;
	return (pip);
}

int	main(int ac, char **av, char **envp)
{
	t_pip	pip;

	if (ac != 5)
	{
		ft_printf("pipex takes 4 parameters:\t <infile> <\"cmd1 [args]\"> <\"cmd2 [args]\"> <outfile>\n");
		return (1);
	}
	else if (!*envp)
	{
		ft_printf("could not fetch environment pointer\n");
		return (1);
	}
	pip = init_struct();
	parse_args(&pip, av);
	parse_paths(&pip, envp);
	exec(&pip, envp);
	clean_up(&pip);
	return (0);
}
