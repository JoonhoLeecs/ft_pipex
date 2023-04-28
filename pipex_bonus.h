/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:09:26 by joonhlee          #+#    #+#             */
/*   Updated: 2023/04/28 15:10:09 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include "getnextline/get_next_line.h"

int		perror_n_return(char *str, int exit_code);
int		init_stdio(int argc, char **argv);
int		ft_strcmp(char *s1, char *s2);
char	*check_heredoc(char **argv, int fci);
char	*nexist_name(void);
void	write_heredoc(int fd, char *limiter);
char	*free_n_return(char *str);
int		parent(int pipefd0, int pipefd1, char *arg, char **envp);
void	setup_fd(int pipefd0, int pipefd1);
int		child(char *arg, char **envp);
int		close_perror_return(int fd, char *str, int code);
char	*find_cmd_path(char *cmd, char **envp);
char	**find_path_env(char **envp, char **cmd);
char	*check_cmd_path(char *cmd, char **dirs);
void	free_double_ptr(char **ptr);

#endif
