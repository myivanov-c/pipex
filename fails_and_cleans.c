/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fails_and_cleans.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykytaivanov <mykytaivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:20:57 by myivanov          #+#    #+#             */
/*   Updated: 2025/07/11 16:01:08 by mykytaivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free (arr);
}

void	cleanup(t_pipex *px)
{
	int		status;
	pid_t	pid;

	close_all_pipes(px->pipes, px->n_cmds - 1);
	free_all_pipes(px->pipes, px->n_cmds - 1);
	close(px->f1);
	close(px->f2);
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == px->last_pid)
			px->last_status = status;
		pid = wait(&status);
	}
}
