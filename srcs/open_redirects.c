/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:48:18 by sclam             #+#    #+#             */
/*   Updated: 2022/03/20 15:03:59 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_fd(int fd, char *file, char *message)
{
	if (fd == -1)
	{
		if (file)
			perror(file);
		if (message)
			ft_putendl_fd(message, 2);
		return (1);
	}
	return (0);
}

static int	open_heredoc(t_cmd *cmd)
{
	char	*str;
	int		fd;

	if (!cmd->heredoc_file)
		return (-1);
	str = ft_strjoin("heredoc/", cmd->heredoc_file);
	if (!str)
		return (-1);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		ft_putendl_fd("Error while open heredoc file", 2);
	free(str);
	return (fd);
}

int	ft_open_infiles(t_cmd *cmd)
{
	int			fdin;
	int			i;
	t_redirect	*tmp;

	fdin = -2;
	tmp = cmd->redir;
	i = infiles_count(tmp);
	while (tmp && i != 0)
	{
		if (tmp->infile || tmp->heredoc)
		{
			if (tmp->infile)
				fdin = open(tmp->infile, O_RDONLY);
			else
				fdin = open_heredoc(cmd);
			if (check_fd(fdin, tmp->infile, NULL))
				return (-1);
			if (--i != 0)
				close(fdin);
		}
		tmp = tmp->next;
	}
	return (fdin);
}

int	ft_open_outfiles(t_cmd *cmd)
{
	t_redirect	*tmp;
	int			out;
	int			i;

	out = -2;
	tmp = cmd->redir;
	i = outfiles_count(tmp);
	while (tmp && i != 0)
	{
		if (tmp->outfile)
		{
			if (tmp->append_mod)
				out = open(tmp->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				out = open(tmp->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (check_fd(out, tmp->outfile, NULL))
				return (-1);
			if (--i != 0)
				close(out);
		}
		tmp = tmp->next;
	}
	return (out);
}

void	exec_redir(t_cmd *cmd)
{
	int	fdout;
	int	fdin;
	int	tmp;

	tmp = dup(1);
	fdin = ft_open_infiles(cmd);
	if (fdin == -1)
		exit(EXIT_FAILURE);
	else if (fdin >= 0)
		dup2(fdin, 0);
	fdout = ft_open_outfiles(cmd);
	if (fdout == -1)
		exit(EXIT_FAILURE);
	else if (fdout >= 0)
		dup2(fdout, 1);
}
