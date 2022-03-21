/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:45:47 by sclam             #+#    #+#             */
/*   Updated: 2022/03/19 18:20:21 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_save_first(t_fd *fd_stct)
{
	fd_stct->tmpin = dup(0);
	fd_stct->tmpout = dup(1);
	fd_stct->fdin = dup(fd_stct->tmpin);
}

int	ft_save_sec(t_cmd *curr, int *fdpipe, t_fd *fd_stct)
{
	dup2(fd_stct->fdin, 0);
	close(fd_stct->fdin);
	if (!curr->next)
		fd_stct->fdout = dup(fd_stct->tmpout);
	else
	{
		if (pipe(fdpipe) == -1)
		{
			perror("pipe: ");
			return (1);
		}
		fd_stct->fdout = fdpipe[1];
		fd_stct->fdin = fdpipe[0];
	}
	dup2(fd_stct->fdout, 1);
	close(fd_stct->fdout);
	return (0);
}

void	ft_restore_fds(t_fd *fd_stct)
{
	close(fd_stct->fdin);
	close(fd_stct->fdout);
	dup2(fd_stct->tmpin, 0);
	dup2(fd_stct->tmpout, 1);
	close(fd_stct->tmpin);
	close(fd_stct->tmpout);
}
