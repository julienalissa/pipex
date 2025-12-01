/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:06:41 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/30 19:07:21 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_here_doc_execute(char *line, int len, int pipe_fd[2], char *delimiter)
{
	write(1, "heredoc> ", 9);
	line = get_next_line(0);
	if (!line)
	{
		perror("gnl");
		exit(1);
	}
	if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
	{
		free(line);
		close(pipe_fd[1]);
		return (-1);
	}
	write(pipe_fd[1], line, ft_strlen(line));
	ft_strlen(line);
	free(line);
	return (0);
}

int	ft_heredoc(char *delimiter)
{
	char	*line;
	int		len;
	int		pipe_fd[2];

	line = NULL;
	len = ft_strlen(delimiter);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		if (ft_here_doc_execute(line, len, pipe_fd, delimiter) == -1)
			break ;
	}
	return (pipe_fd[0]);
}

void	execute_here_doc(t_list *value, char **argv, int argc)
{
	value->fd_file1 = ft_heredoc(argv[2]);
	value->i = 3;
	value->nb_cmd = argc - 4;
}
