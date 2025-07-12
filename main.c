/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykytaivanov <mykytaivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:47:14 by mykytaivano       #+#    #+#             */
/*   Updated: 2025/07/11 17:31:51 by mykytaivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_here_doc_pipeline(int argc, char **argv, t_pipex *px)
{
	int	outfile_error;

	handle_here_doc(argv[2]);
	px->f1 = open(".here_doc_tmp", O_RDONLY);
	if (px->f1 < 0)
		px->f1 = open("/dev/null", O_RDONLY);
	px->f2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	outfile_error = 0;
	if (px->f2 < 0)
	{
		perror("outfile");
		px->f2 = open("/dev/null", O_WRONLY);
		if (px->f2 < 0)
		{
			perror("fallback outfile");
			exit(1);
		}
		outfile_error = 1;
	}
	px->n_cmds = argc - 4;
	px->pipes = malloc_pipes(px->n_cmds - 1);
    if (!px -> pipes)
        return (NULL);
	execute_all_cmds(argv + 3, px);
	return (outfile_error);
}

static int	init_standard_pipeline(int argc, char **argv, t_pipex *px)
{
	int	outfile_error;

	outfile_error = open_files(argv, &px->f1, &px->f2, argc);
	px->n_cmds = argc - 3;
	px->pipes = malloc_pipes(px->n_cmds - 1);
    if (!px -> pipes)
        return (NULL);
	execute_all_cmds(argv + 2, px);
	return (outfile_error);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		outfile_error;

	px.envp = envp;
	parse_args(argc);
	if (is_here_doc(argv[1]))
		outfile_error = init_here_doc_pipeline(argc, argv, &px);
	else
		outfile_error = init_standard_pipeline(argc, argv, &px);
	cleanup(&px);
	if (outfile_error)
		return (1);
	if (WIFEXITED(px.last_status))
		return (WEXITSTATUS(px.last_status));
	else
		return (1);
}
