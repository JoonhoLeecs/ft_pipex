/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:09:26 by joonhlee          #+#    #+#             */
/*   Updated: 2023/04/28 15:08:39 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

int		perror_n_return(char *str, int exit_code);
int		child(int pipefd0, int pipefd1, char *arg, char **envp);
int		parent(int pipefd0, int pipefd1, char *arg, char **envp);
int		close_perror_return(int fd, char *str, int code);
char	*find_cmd_path(char *cmd, char **envp);
char	**find_path_env(char **envp, char **cmd);
char	*check_cmd_path(char *cmd, char **dirs);
void	free_double_ptr(char **ptr);

#endif
