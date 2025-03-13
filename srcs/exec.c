/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:04:02 by imeulema          #+#    #+#             */
/*   Updated: 2025/03/05 09:08:04 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

static void	exec_cmd2(t_pip *pip, char **envp)
{
	dup2(pip->fd[0], STDIN_FILENO);
	dup2(pip->fd_out, STDOUT_FILENO);
	close_fds(pip);
	if (!pip->cmd2_path)
		clean_exit(pip);
	execve(pip->cmd2_path, pip->cmd2_args, envp);
}

static void	exec_cmd1(t_pip *pip, char **envp)
{
	dup2(pip->fd_in, STDIN_FILENO);
	dup2(pip->fd[1], STDOUT_FILENO);
	close_fds(pip);
	if (!pip->cmd1_path)
		clean_exit(pip);
	execve(pip->cmd1_path, pip->cmd1_args, envp);
}

static int	make_fork(t_pip *pip, char *path, int file_fd)
{
	int	pid;

	pid = 1;
	if (path && file_fd != -1)
		pid = fork();
	if (pid < 0)
	{
		perror("fork");
		clean_exit(pip);
	}
	return (pid);
}

void	exec(t_pip *pip, char **envp)
{
	int	pid1;
	int	pid2;

	pid1 = make_fork(pip, pip->cmd1_path, pip->fd_in);
	if (pid1 == 0)
		exec_cmd1(pip, envp);
	pid2 = make_fork(pip, pip->cmd2_path, pip->fd_out);
	if (pid2 == 0)
		exec_cmd2(pip, envp);
	close_fds(pip);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
