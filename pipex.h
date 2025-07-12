/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykytaivanov <mykytaivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:27:02 by mykytaivano       #+#    #+#             */
/*   Updated: 2025/07/11 15:48:04 by mykytaivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "./libft/libft.h"

typedef struct s_pipex
{
	int		f1;
	int		f2;
	int		n_cmds;
	int		**pipes;
	int		last_status;
	pid_t	last_pid;
	char	**envp;
}			t_pipex;

void	parse_args(int argc);
void	handle_here_doc(char *limiter);
void	execute_all_cmds(char **argv, t_pipex *px);
void	cleanup(t_pipex *px);
void	close_all_pipes(int **pipes, int n);
void	free_all_pipes(int **pipes, int n);
void	free_split(char **arr);
void	handle_cmd_error1(int **pipes, int n_pipes, char *cmd);
void	handle_cmd_error2(char **args, int **pipes, int n_pipes);
void	handle_cmd_error3(char **args, char *cd_p, int **pipes, int n_pipes);
void	fork_all_cmds(char **argv, t_pipex *px);
void	wait_all_cmds(t_pipex *px);
void	set_dup(int i, t_pipex *px);
void	run_cmd(char *argv, char **envp, int **pipes, int n_pipes);
int		open_files(char **argv, int *f1, int *f2, int argc);
int		is_here_doc(char *str);
int		**malloc_pipes(int n);
char	*get_cmd_path(char *cmd, char **envp);

#endif
