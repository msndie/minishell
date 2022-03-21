/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkieth <jkieth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:48:43 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/13 19:48:43 by jkieth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lst_del(t_node **lst, t_node *del)
{
	t_node	*tmp;
	t_node	*prev;

	if (*(lst) == del)
	{
		free(del->info);
		free(del->name);
		*(lst) = (*lst)->next;
		free(del);
		return ;
	}
	tmp = (*lst)->next;
	prev = *(lst);
	while (tmp != del && tmp)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	free(tmp->info);
	free(tmp->name);
	free(tmp);
}

int	ft_lst_add_front(t_node **lst, t_node *new)
{
	if (!new)
		return (-1);
	new->next = *lst;
	*lst = new;
	return (0);
}
