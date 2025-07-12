/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykytaivanov <mykytaivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:47:08 by mykytaivano       #+#    #+#             */
/*   Updated: 2025/07/11 15:55:16 by mykytaivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "pipex.h"

void	fork_all_cmds(char **argv, t_pipex *px)
{
	pid_t	fork_id;
	int		i;

	i = 0;
	while (i < px->n_cmds)
	{
		fork_id = fork();
		if (fork_id == 0)
		{
			set_dup(i, px);
			close_all_pipes(px->pipes, px->n_cmds - 1);
			run_cmd(argv[i], px->envp, px->pipes, px->n_cmds - 1);
		}
		else if (i == px->n_cmds - 1)
			px->last_pid = fork_id;
		i++;
	}
}

void	wait_all_cmds(t_pipex *px)
{
	int		status;
	pid_t	wait_pid;

	wait_pid = waitpid(-1, &status, 0);
	while (wait_pid > 0)
	{
		if (wait_pid == px->last_pid && WIFEXITED(status))
			px->last_status = status;
		wait_pid = waitpid(-1, &status, 0);
	}
}
