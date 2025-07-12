/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_bonus.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykytaivanov <mykytaivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:42:21 by mykytaivano       #+#    #+#             */
/*   Updated: 2025/07/07 17:43:00 by mykytaivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_here_doc(char *str)
{
	return (ft_strncmp(str, "here_doc", 9) == 0);
}

static int	create_temp_file(void)
{
	int	fd;

	fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("here_doc temp file");
		exit(1);
	}
	return (fd);
}

static void	write_until_limiter(int fd, char *limiter)
{
	char	*line;
	size_t	lim_len;

	lim_len = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, lim_len) == 0 && line[lim_len] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void	handle_here_doc(char *limiter)
{
	int		tmp_fd;
	int		rfd;
	char	*line;

	tmp_fd = create_temp_file();
	write_until_limiter(tmp_fd, limiter);
	close(tmp_fd);
	rfd = open(".here_doc_tmp", O_RDONLY);
	line = get_next_line(rfd);
	while (line)
	{
		free(line);
		line = get_next_line(rfd);
	}
	close(rfd);
}

