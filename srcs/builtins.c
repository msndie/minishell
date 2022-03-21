/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:42:09 by sclam             #+#    #+#             */
/*   Updated: 2022/03/20 16:32:22 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_cmd *cmd)
{
	int		i;
	t_node	*tmp;

	i = 1;
	*cmd->exit_status = 0;
	while (cmd->args[i])
	{
		if (ft_identif_check(cmd->args[i]) != 0)
		{
			*cmd->exit_status = 1;
			i++;
			continue ;
		}
		tmp = find_list_elem(*cmd->env, cmd->args[i]);
		if (tmp)
			ft_lst_del(cmd->env, tmp);
		i++;
	}
}

void	ft_env(t_cmd *cmd)
{
	t_node	*tmp;

	tmp = *cmd->env;
	while (tmp)
	{
		if (tmp->info)
		{
			ft_putstr_fd(tmp->name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(tmp->info, 1);
		}
		tmp = tmp->next;
	}
	*cmd->exit_status = 0;
}

static int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int		n_flag;
	size_t	i;

	n_flag = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (!check_flag(cmd->args[i]))
			break ;
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', 1);
	*cmd->exit_status = 0;
}
