/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykytaivanov <mykytaivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:58:42 by mykytaivano       #+#    #+#             */
/*   Updated: 2025/07/11 17:32:05 by mykytaivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_dup(int i, t_pipex *px)
{
	if (i == 0)
	{
		if (px->f1 >= 0)
			dup2(px->f1, STDIN_FILENO);
		else
			exit(1);
		dup2(px->pipes[0][1], STDOUT_FILENO);
	}
	else if (i == px->n_cmds - 1)
	{
		dup2(px->pipes[i - 1][0], STDIN_FILENO);
		if (px->f2 >= 0)
			dup2(px->f2, STDOUT_FILENO);
		else
			exit(1);
	}
	else
	{
		dup2(px->pipes[i - 1][0], STDIN_FILENO);
		dup2(px->pipes[i][1], STDOUT_FILENO);
	}
}

void	run_cmd(char *argv, char **envp, int **pipes, int n_pipes)
{
	char	**args;
	char	*cd_p;

	if (!argv || !*argv)
		handle_cmd_error1(pipes, n_pipes, argv);
	args = ft_split(argv, ' ');
	if (!args || !args[0])
		handle_cmd_error2(args, pipes, n_pipes);
	cd_p = get_cmd_path(args[0], envp);
	if (!cd_p)
		handle_cmd_error3(args, cd_p, pipes, n_pipes);
	execve(cd_p, args, envp);
	perror("execve");
	free(cd_p);
	free_split(args);
	free_all_pipes(pipes, n_pipes);
	exit(1);
}

void	execute_all_cmds(char **argv, t_pipex *px)
{
	fork_all_cmds(argv, px);
	close_all_pipes(px->pipes, px->n_cmds - 1);
	wait_all_cmds(px);
}
