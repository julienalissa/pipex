/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+   +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:52:37 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/30 20:52:37 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_remove_quote(char **argv_cmd)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	while (argv_cmd[i])
	{
		str = argv_cmd[i];
		len = ft_strlen(str);
		if (len >= 2 && ((str[0] == '\'' && str[len -1] == '\'')
				|| (str[0] == '"' && str[len - 1] == '"')))
		{
			argv_cmd[i] = ft_substr(str, 1, len -2);
			free(str);
		}
		i++;
	}
}

void	ft_define_value(t_list *value, int argc, char **argv, char **environ)
{
	value->argv = argv;
	value->env = environ;
	value->argc = argc;
	value->argv_cmd = NULL;
	value->fd_file2 = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (value->fd_file2 == -1)
	{
		close(value->fd_file1);
		perror("file2");
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		execute_here_doc(&(*value), argv, argc);
	else
	{
		value->fd_file1 = open(argv[1], O_RDONLY);
		if (value->fd_file1 == -1)
		{
			perror("file1");
			exit (1);
		}
		value->i = 2;
		value->nb_cmd = argc - 3;
	}
}

void	ft_check_less_five_arg(int argcc)
{
	if (argcc < 5)
	{
		write(1, "./pipex file1 cmd1 cmd2 file2\n", 31);
		exit (1);
	}
}

void	ft_free_str(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
