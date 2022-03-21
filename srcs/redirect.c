/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkieth <jkieth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:20:51 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/13 19:32:53 by jkieth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_input(t_cmd *cmd, int *i)
{
	if (add_back_redirect(&cmd->redir, new_redirect()) == 1)
		return (1);
	if (ft_strncmp(cmd->args[(*i)], "<<", 3) == 0)
	{
		last_redirect(cmd->redir)->stop = ft_strdup(cmd->args[++(*i)]);
		if (!last_redirect(cmd->redir)->stop)
			return (1);
		last_redirect(cmd->redir)->heredoc = 1;
		(*i)++;
		return (0);
	}
	else
	{
		last_redirect(cmd->redir)->infile = ft_strdup(cmd->args[++(*i)]);
		if (!last_redirect(cmd->redir)->infile)
			return (1);
		(*i)++;
		return (0);
	}
}

int	redirect_output(t_cmd *cmd, int *i)
{
	if (add_back_redirect(&cmd->redir, new_redirect()) == 1)
		return (1);
	if (ft_strncmp(cmd->args[(*i)], ">>", 3) == 0)
	{
		last_redirect(cmd->redir)->outfile = ft_strdup(cmd->args[++(*i)]);
		if (!last_redirect(cmd->redir)->outfile)
			return (1);
		last_redirect(cmd->redir)->append_mod = 1;
		(*i)++;
		return (0);
	}
	else
	{
		last_redirect(cmd->redir)->outfile = ft_strdup(cmd->args[++(*i)]);
		if (!last_redirect(cmd->redir)->outfile)
			return (1);
		last_redirect(cmd->redir)->append_mod = 0;
		(*i)++;
		return (0);
	}
}

void	redirect_cmd_and_option(t_stct *data, t_cmd *cmd, int *i)
{
	cmd->cmd = ft_strdup(cmd->args[(*i)++]);
	cmd->cmd = find_path(cmd->cmd, data, 0);
	while (cmd->args[(*i)] && (ft_strncmp(cmd->args[(*i)], "<", 2) != 0
			&& ft_strncmp(cmd->args[(*i)], ">", 2) != 0
			&& ft_strncmp(cmd->args[(*i)], ">>", 3) != 0
			&& ft_strncmp(cmd->args[(*i)], "<<", 3) != 0))
	{
		cmd->option = join_str(cmd->option, cmd->args[(*i)]);
		(*i)++;
	}
}

int	redirect_error(void)
{
	ft_putendl_fd("minishell: Error! Memory not allocated.", 2);
	return (1);
}

int	redirect(t_stct *data, t_cmd **cmd)
{
	int	i;

	i = 0;
	while ((*cmd)->args[i])
	{
		if ((*cmd)->args[i][0] == '<')
		{
			if (redirect_input((*cmd), &i) == 1)
				return (redirect_error());
		}
		else if ((*cmd)->args[i][0] == '>')
		{
			if (redirect_output((*cmd), &i) == 1)
				return (redirect_error());
		}
		else
			redirect_cmd_and_option(data, (*cmd), &i);
	}
	free_matrix((*cmd)->args);
	(*cmd)->args = new_args((*cmd)->option, last_word((*cmd)->cmd));
	return (0);
}
