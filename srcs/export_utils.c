/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 18:16:20 by sclam             #+#    #+#             */
/*   Updated: 2022/03/19 20:12:52 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_char_error(char *str, int i)
{
	if ((i == 0 && (str[i] == '=' || (!ft_isalpha(str[i]) && str[i] != '_')))
		|| (i != 0 && !ft_isalpha(str[i]) && str[i] != '_'
			&& !ft_isdigit(str[i])))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return (1);
	}
	return (0);
}

int	ft_check_idtf(char *str, t_cmd *cmd)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i])
	{
		if (i != 0 && str[i] == '=')
			break ;
		if (ft_check_char_error(str, i))
			return (-1);
		i++;
	}
	s = ft_substr(str, 0, i);
	if (s)
	{
		if (find_list_elem(*cmd->env, s))
		{
			free(s);
			return (2);
		}
		free(s);
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

static void	ft_change_value(t_cmd *cmd, char *str)
{
	t_node	*tmp;
	int		i;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	s = ft_substr(str, 0, i);
	if (!s)
		return (ft_putendl_fd("export: not added, malloc error", 2));
	if (ft_strncmp(s, "_", 2) == 0)
		return (free(s));
	tmp = find_list_elem(*cmd->env, s);
	free(tmp->info);
	if (str[i] == '=')
		tmp->info = ft_strdup(str + i + 1);
	else
		tmp->info = NULL;
	free(s);
}

void	ft_add_idtf(char *str, int flag, t_cmd *cmd)
{
	t_node	*tmp;
	int		i;

	i = 0;
	if (flag == -1)
	{
		*cmd->exit_status = 1;
		return ;
	}
	if (flag == 2)
		return (ft_change_value(cmd, str));
	if (ft_lst_add_back(cmd->env, ft_lst_new()) == -1)
		return (ft_putendl_fd("export: not added, malloc error", 2));
	tmp = ft_lst_last(*cmd->env);
	if (flag == 1)
		tmp->name = ft_strdup(str);
	else
	{
		while (str[i] != '=')
			i++;
		tmp->name = ft_substr(str, 0, i);
		tmp->info = ft_strdup(str + i + 1);
	}
}

void	ft_print_export(t_cmd *cmd)
{
	t_node	*copy;
	t_node	*tmp;

	copy = ft_copy_list(*cmd->env);
	ft_merge_sort_list(&copy);
	tmp = copy;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "_", 2) == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (tmp->info)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->info, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	ft_free_lists(copy);
}
