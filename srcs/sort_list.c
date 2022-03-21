/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:56:23 by sclam             #+#    #+#             */
/*   Updated: 2022/03/07 14:22:06 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_left_right(t_node **left, t_node **right, t_node *env)
{
	t_node	*tmp;

	tmp = env;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	*(left) = env;
	*(right) = tmp->next;
	tmp->next = NULL;
}

static t_node	*ft_sorted_merge(t_node *left, t_node *right)
{
	t_node	*res;

	if (!left)
		return (right);
	else if (!right)
		return (left);
	if (ft_strncmp(left->name, right->name, ft_strlen(left->name)) <= 0)
	{
		res = left;
		res->next = ft_sorted_merge(left->next, right);
	}
	else
	{
		res = right;
		res->next = ft_sorted_merge(left, right->next);
	}
	return (res);
}

void	ft_merge_sort_list(t_node **env)
{
	t_node	*tmp;
	t_node	*left;
	t_node	*right;

	tmp = *(env);
	if (!tmp || !tmp->next)
		return ;
	ft_left_right(&left, &right, tmp);
	ft_merge_sort_list(&left);
	ft_merge_sort_list(&right);
	*(env) = ft_sorted_merge(left, right);
}
