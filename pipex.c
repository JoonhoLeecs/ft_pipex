/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:08:57 by joonhlee          #+#    #+#             */
/*   Updated: 2023/04/28 15:01:36 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	pipefd[2];
	int	pid;

	if (argc != 5)
		return (perror_n_return("invalid output", 1));
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		return (perror_n_return("open", 1));
	fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
		return (perror_n_return("open", 1));
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if (pipe(pipefd) == -1)
		return (perror_n_return("pipe", 1));
	pid = fork();
	if (pid == -1)
		return (perror_n_return("fork", 1));
	else if (pid == 0)
		return (child(pipefd[0], pipefd[1], argv[2], envp));
	else
		return (parent(pipefd[0], pipefd[1], argv[3], envp));
}

int	perror_n_return(char *str, int exit_code)
{
	perror(str);
	return (exit_code);
}

int	child(int pipefd0, int pipefd1, char *arg, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	close(pipefd0);
	dup2(pipefd1, STDOUT_FILENO);
	close(pipefd1);
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

int	close_perror_return(int fd, char *str, int code)
{
	close(fd);
	perror(str);
	return (code);
}
