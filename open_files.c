/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykytaivanov <mykytaivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:43:30 by mykytaivano       #+#    #+#             */
/*   Updated: 2025/07/11 17:32:12 by mykytaivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_infile(char *file, int *f1)
{
	*f1 = open(file, O_RDONLY);
	if (*f1 < 0)
	{
		perror(file);
		*f1 = open("/dev/null", O_RDONLY);
		if (*f1 < 0)
		{
			perror("fallback infile");
			exit(1);
		}
	}
}

static int	open_outfile(char *file, int *f2)
{
	*f2 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*f2 < 0)
	{
		perror(file);
		*f2 = open("/dev/null", O_WRONLY);
		if (*f2 < 0)
		{
			perror("fallback outfile");
			exit(1);
		}
		return (1);
	}
	return (0);
}

int	open_files(char **argv, int *f1, int *f2, int argc)
{
	int	outfile_error;

	open_infile(argv[1], f1);
	outfile_error = open_outfile(argv[argc - 1], f2);
	return (outfile_error);
}
