/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:34:06 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/17 21:27:07 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*free_matrix(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
			free(strs[i++]);
		free(strs);
		strs = NULL;
	}
	return (NULL);
}

void	*ft_free_lists(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node->next;
		free(node->name);
		free(node->info);
		free(node);
		node = tmp;
	}
	node = NULL;
	return (NULL);
}

void	free_redirect(t_redirect *redirect)
{
	t_redirect	*temp;

	while (redirect)
	{
		temp = redirect->next;
		if (redirect->infile)
			free(redirect->infile);
		if (redirect->outfile)
			free(redirect->outfile);
		if (redirect->stop)
			free(redirect->stop);
		free(redirect);
		redirect = temp;
	}
}

void	ft_free_stcs(t_stct *stct)
{
	if (stct->cmd)
		stct->cmd = free_cmd(stct->cmd);
}

void	*free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->heredoc_file)
			free(cmd->heredoc_file);
		if (cmd->args)
			free_matrix(cmd->args);
		if (cmd->option)
			free_matrix(cmd->option);
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->redir)
			free_redirect(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
	return (0);
}
