/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:23:10 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/12 17:56:13 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	checker_different(char **strs, int *i, int *j, int *count)
{
	if (strs[(*i)][(*j)] == '<')
	{
		while (strs[(*i)][(*j)] == '<')
		{
			(*j)++;
			(*count)++;
		}
		if (strs[(*i)][(*j)] == '>')
			(*count) = 3;
	}
	else if (strs[(*i)][(*j)] == '>')
	{
		while (strs[(*i)][(*j)] == '>')
		{
			(*j)++;
			(*count)++;
		}
		if (strs[(*i)][(*j)] == '<')
			(*count) = 3;
	}
}

int	first_check_redirect(char **strs, int i, int j, int flag)
{
	int	count;

	count = 0;
	while (strs[i])
	{
		while (strs[i][j])
		{
			if (strs[i][j] == '<' || strs[i][j] == '>')
			{
				checker_different(strs, &i, &j, &count);
				if (count > 2)
					return (-1);
				count = 0;
				flag = 1;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (flag);
}

int	checker(char *arg)
{
	if (ft_strncmp(arg, "<", 2) == 0)
		return (0);
	else if (ft_strncmp(arg, ">", 2) == 0)
		return (0);
	else if (ft_strncmp(arg, "<<", 3) == 0)
		return (0);
	else if (ft_strncmp(arg, ">>", 3) == 0)
		return (0);
	return (1);
}

int	second_check_redirect(char **strs, int i, int flag)
{
	int	wc;

	wc = 0;
	while (strs[i])
	{
		if (checker(strs[i]) == 0)
		{
			if (wc > 1)
				flag = 1;
			wc = 0;
			i++;
			while (strs[i] && checker(strs[i]) != 0)
			{
				wc++;
				i++;
			}
			if ((flag == 1 && wc != 1) || (flag == 0 && (wc < 1 || wc > 3)))
				return (1);
			continue ;
		}
		else
			wc++;
		i++;
	}
	return (0);
}

int	check_redirect(t_cmd **cmd)
{
	int	first_check;

	first_check = first_check_redirect((*cmd)->args, 0, 0, 0);
	if (first_check == 0)
		return (0);
	else if (first_check == -1)
	{
		ft_putendl_fd("minishell: syntax error with redirect", 2);
		return (-1);
	}
	else if (second_check_redirect((*cmd)->args, 0, 0) == 1)
	{
		ft_putendl_fd("minishell: syntax error with redirect", 2);
		return (-1);
	}
	return (1);
}
