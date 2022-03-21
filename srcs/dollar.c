/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:07:02 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/16 21:30:28 by jkieth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (1);
	return (0);
}

char	*without_quote(char *str, int quote)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	if (quote == 0 || str[0] == '\0')
		return (str);
	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == 92 && (str[i + 1] == 34 || str[i + 1] == 39))
		{
			new_str = ft_charjoin(new_str, str[++i]);
			i++;
			continue ;
		}
		if (str[i] != 34 && str[i] != 39)
			new_str = ft_charjoin(new_str, str[i]);
		i++;
	}
	free(str);
	return (new_str);
}

void	check_valid_env(char *str, int *i, int j)
{
	while (str[(*i)] && (ft_isalnum(str[(*i)]) || str[(*i)] == '_'))
		(*i)++;
	if (ft_isdigit(str[j + 1]))
	{
		(*i) = j + 2;
		return ;
	}
	if (str[(*i)] == '?' && str[(*i) - 1] == '$')
		(*i)++;
}

void	find_env_elem(t_stct *data, char *str, char **final_str, int *i)
{
	t_node	*env;
	char	*exit_status;
	char	*temp;
	int		j;

	j = (*i)++;
	check_valid_env(str, &(*i), j);
	temp = ft_substr(str, j, (*i) - j);
	if (ft_strncmp(temp, "$_", 3) == 0)
		(*final_str) = ft_strjoin_free((*final_str), data->last_arg);
	else if (ft_strncmp(temp, "$?", 3) == 0)
	{
		exit_status = ft_itoa(data->exit_status);
		(*final_str) = ft_strjoin_free((*final_str), exit_status);
		free(exit_status);
	}
	else
	{
		env = find_list_elem(data->env, temp + 1);
		if (env)
			(*final_str) = ft_strjoin_free((*final_str), env->info);
		else
			(*final_str) = ft_strjoin_free((*final_str), "\0");
	}
	free(temp);
}

char	*dollar(t_stct *data, char *str)
{
	char	*final_str;
	int		i;
	int		count_quote;

	i = 0;
	count_quote = 0;
	final_str = NULL;
	while (str[i])
	{
		if (str[i] == 39 && str[i - 1] != 92)
			count_quote++;
		if (str[i] == '$' && count_quote % 2 == 0)
		{
			find_env_elem(data, str, &final_str, &i);
			continue ;
		}
		final_str = ft_charjoin(final_str, str[i]);
		i++;
	}
	final_str = without_quote(final_str, 34);
	free(str);
	return (final_str);
}
