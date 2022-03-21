/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:20:25 by sclam             #+#    #+#             */
/*   Updated: 2022/03/21 16:02:36 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	event(void)
{
	return (0);
}

static int	heredoc_helper(t_cmd *cmd)
{
	char	*str;
	int		fd;

	if (!cmd->heredoc_file)
		return (-1);
	str = ft_strjoin("heredoc/", cmd->heredoc_file);
	if (!str)
	{
		free(cmd->heredoc_file);
		cmd->heredoc_file = NULL;
		return (-1);
	}
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(str);
	return (fd);
}

static void	heredoc_read(t_redirect *redir, t_cmd *cmd)
{
	int		fd;
	char	*str;

	fd = heredoc_helper(cmd);
	if (fd == -1)
		return (ft_putendl_fd("Can't open heredoc file", 2));
	g_stage = 2;
	rl_event_hook = event;
	while (1)
	{
		str = readline("> ");
		if (g_stage == 228)
			break ;
		if (str)
		{
			if (!ft_strncmp(str, redir->stop, ft_strlen(str) + 1))
				break ;
			ft_putendl_fd(str, fd);
			free(str);
		}
		else
			break ;
	}
	free(str);
	close(fd);
}
  
void	ft_heredoc(t_cmd *cmd)
{
	t_cmd		*tmp;
	t_redirect	*temp;
	int			i;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		temp = tmp->redir;
		while (temp)
		{
			if (temp->heredoc)
			{
				if (!tmp->heredoc_file)
					tmp->heredoc_file = ft_itoa(i++);
				heredoc_read(temp, tmp);
				if (g_stage == 228)
					return ;
				if (!tmp->heredoc_file)
					break ;
			}
			temp = temp->next;
		}
		tmp = tmp->next;
	}
}
