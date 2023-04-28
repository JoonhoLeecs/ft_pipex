/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:08:57 by joonhlee          #+#    #+#             */
/*   Updated: 2023/04/28 16:52:28 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int		first_cmd_ind;
	int		cmd_ind;
	int		pipefd[2];
	int		pid;

	first_cmd_ind = init_stdio(argc, argv);
	if (first_cmd_ind < 2)
		return (first_cmd_ind);
	cmd_ind = argc - 2;
	while (cmd_ind > first_cmd_ind)
	{
		if (pipe(pipefd) == -1)
			return (perror_n_return("pipe", 1));
		pid = fork();
		if (pid == -1)
			return (perror_n_return("fork", 1));
		else if (pid > 0)
			return (parent(pipefd[0], pipefd[1], argv[cmd_ind], envp));
		else if (pid == 0)
		{
			setup_fd(pipefd[0], pipefd[1]);
			if (cmd_ind-- == first_cmd_ind + 1)
				return (child(argv[first_cmd_ind], envp));
		}
	}
}

int	init_stdio(int argc, char **argv)
{
	char	*infile;
	int		fd_in;
	int		fd_out;
	int		first_cmd_ind;

	if (argc < 5)
		return (perror_n_return("invalid input:", 1));
	first_cmd_ind = 2 + (ft_strcmp(argv[1], "here_doc") == 0);
	infile = check_heredoc(argv, first_cmd_ind);
	if (infile == 0)
		return (perror_n_return("here doc:", 1));
	fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
		return (perror_free("open", 1, first_cmd_ind, infile));
	if (first_cmd_ind == 2)
		fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd_out = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd_out == -1)
		return (perror_free("open", 1, first_cmd_ind, infile));
	clear_infile(first_cmd_ind, infile);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	return (first_cmd_ind);
}

void	setup_fd(int pipefd0, int pipefd1)
{
	close(pipefd0);
	dup2(pipefd1, STDOUT_FILENO);
	close(pipefd1);
}

int	child(char *arg, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(arg, ' ');
	if (cmd_args == 0)
		return (close_perror_return(STDOUT_FILENO, "malloc", 1));
	cmd_path = find_cmd_path(cmd_args[0], envp);
	if (cmd_path == 0)
		return (close_perror_return(STDOUT_FILENO, "malloc", 1));
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free_double_ptr(cmd_args);
		close(STDOUT_FILENO);
		perror("cmd");
		return (127);
	}
	return (0);
}

int	parent(int pipefd0, int pipefd1, char *arg, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	close(pipefd1);
	dup2(pipefd0, STDIN_FILENO);
	close(pipefd0);
	cmd_args = ft_split(arg, ' ');
	if (cmd_args == 0)
		return (close_perror_return(STDOUT_FILENO, "malloc", 1));
	cmd_path = find_cmd_path(cmd_args[0], envp);
	if (cmd_path == 0)
		return (close_perror_return(STDOUT_FILENO, "malloc", 1));
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free_double_ptr(cmd_args);
		close(STDOUT_FILENO);
		perror("cmd");
		return (127);
	}
	return (0);
}
