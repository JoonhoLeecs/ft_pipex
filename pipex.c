/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:08:57 by joonhlee          #+#    #+#             */
/*   Updated: 2023/04/26 20:25:15 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	*infile;
	// char	*cmd1;
	// char	*cmd2;
	char	*outfile;
	int	fd_in;
	int	fd_out;
	int	pipefd[2];
	int	pid;
	int	stdout;
	char	**cmd_args;
	char	*cmd_path;

	if (argc != 5)
	{
		perror("invalid output:");
		return (1);
	}
	infile = argv[1];
	outfile = argv[4];
	fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
	{
		perror("open");
		return (1);
	}
	fd_out = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
	{
		perror("open");
		return (1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	stdout = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		// printf("child\n");
		close(pipefd[0]);
		dup2(fd_in, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		cmd_args = ft_split(argv[2], ' ');
		cmd_path = find_cmd_path(cmd_args[0], envp);
		if (cmd_path == 0)
		{
			cmd_path = cmd_args[0];
			// perror("cmd:");
			// write(STDOUT_FILENO, "", 1);
			// close(STDOUT_FILENO);
			// return (127);
		}
		if (execve(cmd_path, cmd_args, envp) == -1)
		{
			close(STDOUT_FILENO);
			perror("cmd");
			return (127);
		}

	}
	else
	{
		// printf("parent\n");
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(pipefd[0]);
		cmd_args = ft_split(argv[3], ' ');
		cmd_path = find_cmd_path(cmd_args[0], envp);
		if (cmd_path == 0)
		{
			cmd_path = cmd_args[0];
			// perror("cmd:");
			// write(STDOUT_FILENO, "\0", 1);
			// close(STDOUT_FILENO);
			// return (127);
			// perror("cmd:command not found");
			// return (3);
		}
		if (execve(cmd_path, cmd_args, envp) == -1)
		{
			close(STDOUT_FILENO);
			perror("cmd");
			return (127);
		}
	}

}

void	print_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		printf("[%d]:%s\n", i, ptr[i]);
		i++;
	}
}

char	*find_cmd_path(char *cmd, char **envp)
{
	int	i;
	// char	*env_path;
	char	**dirs;
	char	*cmd_path;
	int		check;

	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	// printf("envp PATH line is %s\n", (envp[i] + 5));
	// printf("cmd is %s\n", cmd);
	dirs = ft_split((envp[i] + 5), ':');
	i = 0;
	check = 0;
	while (dirs[i])
	{
		cmd_path = ft_strjoin(dirs[i], cmd);
		// printf("cmd_path is %s\n", cmd_path);
		if (access(cmd_path, F_OK) == 0)
		{
			check = 1;
			break ;
		}
		free (cmd_path);
		i++;
	}
	free (cmd);
	i = 0;
	while (dirs[i])
	{
		free(dirs[i]);
		i++;
	}
	free (dirs);
	if (check == 0)
	{
		// perror("cmd:command not found");
		return (0);
	}
	else
	{
		return (cmd_path);
	}
}
