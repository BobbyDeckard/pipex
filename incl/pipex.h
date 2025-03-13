/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:02:38 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/05 09:02:39 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// LIBRARIES
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

// STRUCTS
typedef struct s_pip
{
	char	**cmd1_args;
	char	**cmd2_args;
	char	**paths;
	char	*cmd1_path;
	char	*cmd2_path;
	int		fd[2];
	int		fd_in;
	int		fd_out;
}	t_pip;

// FUNCTS
void	clean_exit(t_pip *pip);
void	clean_up(t_pip *pip);
void	close_fds(t_pip *pip);
void	exec(t_pip *pip, char **envp);
void	free_args(char **args);
void	free_paths(t_pip *pip);
void	parse_args(t_pip *pip, char **av);
void	parse_paths(t_pip *pip, char **av);
char	**ft_split_path(const char *s, char c);

#endif
