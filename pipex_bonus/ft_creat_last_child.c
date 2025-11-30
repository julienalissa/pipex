/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_last_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+   +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:51:29 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/30 20:51:38 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_fork_it(t_list *value)
{
	value->fork_id = fork();
	if (value->fork_id == -1)
	{
		ft_close_prev_files(&(*value));
		perror("fork");
		exit(1);
	}
}

void	ft_dup_last(t_list *value)
{
	if (dup2(value->p_pipe, 0) == -1)
	{
		ft_close_prev_files(&(*value));
		perror("dup");
		exit(1);
	}
	if (dup2(value->fd_file2, 1) == -1)
	{
		ft_close_prev_files(&(*value));
		perror("dup");
		exit(1);
	}
}

void	ft_process_last_fork(t_list *value)
{
	if (value->fork_id == 0)
	{
		ft_dup_last(&(*value));
		ft_close_prev_files(&(*value));
		value->argv_cmd = ft_split(value->argv[value->argc - 2], ' ');
		ft_remove_quote(value->argv_cmd);
		value->path = get_path(value->argv_cmd[0], value->env);
		if (!value->path)
		{
			perror("path");
			exit(1);
		}
		execve(value->path, value->argv_cmd, value->env);
		exit(1);
	}
}

void	ft_creat_last_child(t_list *value)
{
	ft_fork_it(&(*value));
	ft_process_last_fork(&(*value));
	ft_close_prev_files(&(*value));
	value->i = 0;
	while (value->i < value->nb_cmd)
	{
		wait(&value->status);
		value->i = value->i + 1;
	}
}
