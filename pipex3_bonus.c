/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:06:45 by joonhlee          #+#    #+#             */
/*   Updated: 2023/04/28 15:35:54 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	close_perror_return(int fd, char *str, int code)
{
	close(fd);
	perror(str);
	return (code);
}

int	perror_n_return(char *str, int exit_code)
{
	perror(str);
	return (exit_code);
}

int	perror_free(char *str, int code, int fci, char *infile)
{
	if (fci == 3)
		free (infile);
	perror(str);
	return (code);
}
