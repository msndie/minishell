/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:43:31 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/17 22:49:29 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redirect	*new_redirect(void)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->infile = NULL;
	redirect->outfile = NULL;
	redirect->stop = NULL;
	redirect->append_mod = 0;
	redirect->heredoc = 0;
	redirect->next = NULL;
	return (redirect);
}

t_redirect	*last_redirect(t_redirect *redirect)
{
	t_redirect	*temp;

	temp = redirect;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

int	add_back_redirect(t_redirect **redirect, t_redirect *new)
{
	t_redirect	*tmp;

	if (!new)
		return (1);
	if (!*redirect)
	{
		*redirect = new;
		return (0);
	}
	else
	{
		tmp = last_redirect(*redirect);
		tmp->next = new;
	}
	return (0);
}

int	outfiles_count(t_redirect *redir)
{
	int			i;
	t_redirect	*tmp;

	i = 0;
	tmp = redir;
	while (tmp)
	{
		if (tmp->outfile)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	infiles_count(t_redirect *redir)
{
	int			i;
	t_redirect	*tmp;

	i = 0;
	tmp = redir;
	while (tmp)
	{
		if (tmp->infile || tmp->stop)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
