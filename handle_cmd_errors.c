/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykytaivanov <mykytaivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:45:28 by mykytaivano       #+#    #+#             */
/*   Updated: 2025/07/11 17:33:14 by mykytaivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_cmd_error1(int **pipes, int n_pipes, char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found", 19);
	write(2, "\n", 1);
	free_all_pipes(pipes, n_pipes);
	exit(127);
}

void	handle_cmd_error2(char **args, int **pipes, int n_pipes)
{
	if (args && args[0])
		write(2, args[0], ft_strlen(args[0]));
	else
		write(2, "(null)", 6);
	write(2, ": command not found", 19);
	write(2, "\n", 1);
	free_split(args);
	free_all_pipes(pipes, n_pipes);
	exit(127);
}

void	handle_cmd_error3(char **args, char *cd_p, int **pipes, int n_pipes)
{
	if (args && args[0])
		write(2, args[0], ft_strlen(args[0]));
	else
		write(2, "(null)", 6);
	write(2, ": command not found", 19);
	write(2, "\n", 1);
	free_split(args);
	free_all_pipes(pipes, n_pipes);
	free(cd_p);
	exit(127);
}
