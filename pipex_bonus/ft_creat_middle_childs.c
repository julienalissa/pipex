/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_middle_childs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+   +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:52:51 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/30 20:52:57 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_creat_pipe_and_fork(t_list *value)
{
	if (pipe(value->n_pipe) == -1)
	{
		ft_close_prev_files(value);
		perror("pipe");
		exit(1);
	}
	value->fork_id = fork();
	if (value->fork_id == -1)
	{
		ft_close_prev_and_n_pipe(value);
		perror("pipe");
		exit(1);
	}
}

void	dup_it(t_list *value)
{
	if (dup2(value->p_pipe, 0) == -1)
	{
		ft_close_prev_and_n_pipe(value);
		perror("dup2");
		exit(1);
	}
	if (dup2(value->n_pipe[1], 1) == -1)
	{
		ft_close_prev_and_n_pipe(value);
		perror("dup2");
		exit(1);
	}
}

void	ft_process_middle_childs(t_list *value)
{
	if (value->fork_id == 0)
	{
		dup_it(value);
		ft_close_prev_and_n_pipe(value);
		ft_is_space(value->argv[value->i]);
		value->argv_cmd = ft_split(value->argv[value->i], ' ');
		ft_remove_quote(value->argv_cmd);
		value->path = get_path(value->argv_cmd[0], value->env);
		if (!value->path)
		{
			perror("path");
			ft_free_str(value->argv_cmd);
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

void	ft_creat_middle_childs(t_list *value)
{
	while (value->i < value->nb_cmd)
	{
		ft_creat_pipe_and_fork(value);
		ft_process_middle_childs(value);
		ft_close_non_use(value);
		value->p_pipe = value->n_pipe[0];
		value->i++;
	}
}
