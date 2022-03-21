/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkieth <jkieth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:47:42 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/13 19:49:31 by jkieth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_equally(char *str)
{
	int	index;

	index = 0;
	while (*str++ != '=')
		index++;
	return (index);
}

t_node	*ft_lst_new(void)
{
	t_node	*tmp;

	tmp = malloc(sizeof(t_node));
	if (tmp == NULL)
		return (0);
	tmp->next = NULL;
	tmp->info = NULL;
	tmp->name = NULL;
	return (tmp);
}

int	ft_lst_size(t_node *lst)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_node	*ft_lst_last(t_node *lst)
{
	t_node	*tmp;

	tmp = lst;
	while (lst && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	ft_lst_add_back(t_node **lst, t_node *new)
{
	t_node	*tmp;

	if (!new)
		return (-1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	else
	{
		tmp = ft_lst_last(*lst);
		tmp->next = new;
	}
	return (0);
}
