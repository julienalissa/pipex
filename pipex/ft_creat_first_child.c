/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_first_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+   +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:53:07 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/30 20:53:07 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_creat_pipe_and_fork_it(t_list *value)
{
	if (pipe(value->n_pipe) == -1)
	{
		ft_close_files(&(*value));
		perror("pipe");
		exit (1);
	}
	value->fork_id = fork();
	if (value->fork_id == -1)
	{
		ft_close_files_and_n_pipe(&(*value));
		perror("fork");
		exit(1);
	}
}

void	ft_process_first_child(t_list *value)
{
	if (value->fork_id == 0)
	{
		if (dup2(value->fd_file1, 0) == -1)
		{
			ft_close_files_and_n_pipe(&(*value));
			exit(1);
		}
		if (dup2(value->n_pipe[1], 1) == -1)
		{
			ft_close_files_and_n_pipe(&(*value));
			exit(1);
		}
		ft_close_files_and_n_pipe(&(*value));
		value->argv_cmd = ft_split(value->argv[value->i], ' ');
		ft_remove_quote(value->argv_cmd);
		value->path = get_path(value->argv_cmd[0], value->env);
		if (!value->path)
		{
			ft_free_str(value->argv_cmd);
			perror("path");
			exit(1);
		}
		if (execve(value->path, value->argv_cmd, value->env) == -1)
		{
			free(value->path);
			ft_free_str(value->argv_cmd);
			perror("execeve");
			exit(1);
		}

	}
}

void	ft_creat_first_child(t_list *value)
{
	ft_creat_pipe_and_fork_it(&(*value));
	ft_process_first_child(&(*value));
	value->p_pipe = value->n_pipe[0];
	ft_close_not_used_files(&(*value));
	value->i++;
}
