/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:12:15 by sclam             #+#    #+#             */
/*   Updated: 2022/03/19 19:57:42 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_restore_lvl(t_node *env)
{
	t_node	*tmp;

	if (ft_lst_add_back(&env, ft_lst_new()) == -1)
		ft_putendl_fd("Error: SHLVL\n", 2);
	else
	{
		tmp = ft_lst_last(env);
		tmp->name = ft_strdup("SHLVL");
		tmp->info = ft_itoa(1);
	}
}

void	increment_lvl(t_node *env)
{
	t_node	*tmp;
	int		lvl;

	lvl = 0;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "SHLVL", 6) == 0)
		{
			if (tmp->info)
			{
				lvl = ft_atoi(tmp->info);
				free(tmp->info);
			}
			tmp->info = ft_itoa(lvl + 1);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		ft_restore_lvl(env);
}

void	env_lists(t_stct *data, char **env, int i)
{
	t_node	*tmp;
	char	**strs;

	while (env[i])
	{
		if (i == 0)
		{
			data->env = ft_lst_new();
			tmp = data->env;
		}
		else
		{
			if (ft_strncmp(env[i], "OLDPWD", 6) == 0)
			{
				i++;
				continue ;
			}
			ft_lst_add_back(&tmp, ft_lst_new());
			tmp = tmp->next;
		}
		strs = ft_split(env[i++], '=');
		tmp->name = ft_strdup(strs[0]);
		tmp->info = ft_strdup(strs[1]);
		free_matrix(strs);
	}
}

t_node	*ft_copy_list(t_node *orig)
{
	t_node	*copy;
	t_node	*tmp_copy;
	t_node	*tmp_orig;

	copy = NULL;
	tmp_orig = orig;
	while (tmp_orig)
	{
		if (ft_lst_add_back(&copy, ft_lst_new()) == -1)
			return (ft_free_lists(copy));
		tmp_copy = ft_lst_last(copy);
		tmp_copy->name = ft_strdup(tmp_orig->name);
		if (!tmp_copy->name)
			return (ft_free_lists(copy));
		if (tmp_orig->info)
		{
			tmp_copy->info = ft_strdup(tmp_orig->info);
			if (!tmp_copy->info)
				return (ft_free_lists(copy));
		}
		tmp_orig = tmp_orig->next;
	}
	return (copy);
}

t_node	*find_list_elem(t_node *env_list, char *name)
{
	t_node	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(name, tmp->name, ft_strlen(name) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
