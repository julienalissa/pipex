#include "poulet.h"

int	ft_heredoc(char *delimiter, t_list *value)
{
	char	*line;
	int		len;
	int		pipe_fd[2];

	len = 0;
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
		{
			perror("gnl");
			exit(1);
		}
		len = ft_strlen(delimiter);
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
		{
			close(pipe_fd[1]);

			break;
		}
		else
		{
			free(line);
			write(pipe_fd[1], line, ft_strlen(line));
		}

	}
	value->i = 4;
	return (pipe_fd[0]);
}

void	ft_define_value(t_list *value, int argc, char **argv, char **environ)
{
	value->argv = argv;
	value->env = environ;
	value->argc = argc;
	value->argv_cmd = NULL;
	value->i = 3;
	value->nb_cmd = argc - 3;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		value->fd_file1 = ft_heredoc(argv[2], value);
		if (value->fd_file1 == -1)
		{
			perror("here_doc");
			exit(1);
		}
		value->i = 4;
		value->fd_file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (value->fd_file2 == -1)
		{
			close(value->fd_file1);
			perror("file2");
			exit(1);
		}
	}
	else
	{
		value->fd_file1 = open(argv[1], O_RDONLY);
		if (value->fd_file1 == -1)
		{
			perror("file1");
			exit (1);
		}
		value->fd_file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (value->fd_file2 == -1)
		{
			close(value->fd_file1);
			perror("file2");
			exit(1);
		}
	}
}


void	ft_close_all(t_list *value)
{
	close(value->fd_file1);
	close(value->fd_file2);
	close(value->n_pipe[0]);
	close(value->n_pipe[1]);
}

void	ft_close_fd_files(t_list *value)
{
	close(value->fd_file1);
	close(value->fd_file2);
}

void	ft_close_middle(t_list *value)
{
	close(value->p_pipe);
	close(value->n_pipe[0]);
	close(value->n_pipe[1]);
	close(value->fd_file2);
}

void	ft_close_middle_v2(t_list *value)
{
	close(value->p_pipe);
	close(value->n_pipe[1]);
	close(value->fd_file2);
}

int	main(int argc, char **argv, char **environ)
{
	t_list	value;

	if (argc < 5)
	{
		write(1, "./pipex file1 cmd1 cmd2 file2\n", 31);
		return (1);
	}
	ft_define_value(&value, argc, argv, environ);
	if (pipe(value.n_pipe) == -1)
	{
		ft_close_fd_files(&value);
		perror("pipe");
		return (1);
	}

		value.fork_id = fork();


		if (value.fork_id == -1)
		{
			ft_close_fd_files(&value);
			close(value.n_pipe[0]);
			close(value.n_pipe[1]);
			perror("fork");
			exit(1);
		}


		if (value.fork_id == 0)
		{
			if (dup2(value.fd_file1, 0) == -1)
			{
				ft_close_all(&value); // sur le parent close n_pipe 0 et 1 et f1 et f2
				exit(1);
			}
			if (dup2(value.n_pipe[1], 1) == -1)
			{
				ft_close_all(&value); // sur le parent close n_pipe 0 et 1 et f1 et f2
				exit(1);
			}
			ft_close_all(&value);
			value.argv_cmd = ft_split(argv[2], ' ');
			value.path = get_path(value.argv_cmd[0], value.env);
			execve(value.path, value.argv_cmd, value.env);
			perror("execeve");
			exit(1);
		}

		value.p_pipe = value.n_pipe[0];
		close(value.fd_file1);
		close(value.n_pipe[1]);
		while (value.i < argc - 2)
		{
			if (pipe(value.n_pipe) == -1)
			{
				close(value.p_pipe);
				close(value.fd_file2);
				perror("pipe");
				exit(1);
			}
			value.fork_id = fork();
			if (value.fork_id == -1)
			{
				ft_close_middle(&value);
				perror("pipe");
				exit(1);
			}
			if (value.fork_id == 0)
			{
				if (dup2(value.p_pipe, 0) == -1)
				{
					ft_close_middle_v2(&value);
					perror("dup2");
					exit(1); //check_wait pour close parent commen ft_close_middle
				}
				if (dup2(value.n_pipe[1], 1) == -1)
				{
					ft_close_middle_v2(&value);
					perror("dup2");
					exit(1);  //check_wait pour close parent commen ft_close_middle
				}
				ft_close_middle(&value);
				value.argv_cmd = ft_split(argv[value.i], ' ');
				value.path = get_path(value.argv_cmd[0], value.env);
				execve(value.path, value. argv_cmd, value.env);
				exit(1);
			}
			close(value.p_pipe);
			close(value.n_pipe[1]);
			value.p_pipe = value.n_pipe[0];
			value.i++;
		}




	value.fork_id = fork();
	if (value.fork_id == -1)
	{
		close(value.p_pipe);
		close(value.fd_file2);
		perror("fork");
		exit(1);
	}
	if (value.fork_id == 0)
	{
		if (dup2(value.p_pipe, 0) == -1)
		{
			close(value.p_pipe);
			close(value.fd_file2);
			perror("dup");
			exit(1); // close meme chose dans le pere
		}
		if (dup2(value.fd_file2, 1)  == -1)
		{
			close(value.p_pipe);
			close(value.fd_file2);
			perror("dup");
			exit(1); // close meme chose dansl epere
		}
		close(value.p_pipe);
		close(value.fd_file2);
		value.argv_cmd = ft_split(argv[argc - 2] , ' ');
		value.path = get_path(value.argv_cmd[0], value.env);
		execve(value.path, value.argv_cmd, value.env);
		exit(1);
	}
	close(value.p_pipe);
	close(value.fd_file2);
	remove("aa");
	value.i = 0;
	while (value.i < value.nb_cmd)
	{
		wait(&value.status);
		value.i = value.i + 1;
	} // faire waitpid pour close en fonction des fd

}
