/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:34:44 by sclam             #+#    #+#             */
/*   Updated: 2022/03/19 18:30:58 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_name_and_info(t_node *env)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = ft_strlen(env->name);
	if (env->info)
		j = ft_strlen(env->info);
	else
		j = 0;
	str = malloc(i + j + 2);
	if (!str)
		return (NULL);
	j = 0;
	ft_strlcpy(str, env->name, i + 2);
	if (env->info)
	{
		str[i++] = '=';
		while (env->info[j])
			str[i++] = env->info[j++];
	}
	str[i] = '\0';
	return (str);
}

char	**ft_env_to_arr(t_node *env_list)
{
	char	**env;
	t_node	*tmp;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (ft_lst_size(env_list) + 1));
	if (!env)
		return (NULL);
	tmp = env_list;
	while (tmp)
	{
		env[i] = ft_name_and_info(tmp);
		if (!env[i])
			return (free_matrix(env));
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
