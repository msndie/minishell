/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkieth <jkieth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:09:13 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/13 13:59:14 by jkieth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_spaces(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] == '<' || str[i] == '>')
				i++;
			if (str[i] != ' ')
				count++;
			continue ;
		}
		if ((str[i + 1] == '<' || str[i + 1] == '>') && str[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

char	*new_redirect_str(char *str, int i, int j)
{
	char	*new_str;

	if (count_spaces(str) == 0)
		return (ft_strdup(str));
	new_str = malloc(sizeof(char) * (ft_strlen(str) + count_spaces(str) + 1));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		while (str[i] == '<' || str[i] == '>')
			new_str[j++] = str[i++];
		if ((str[i - 1] == '<' || str[i - 1] == '>') && str[i] != ' ')
			new_str[j++] = ' ';
		if ((str[i + 1] == '<' || str[i + 1] == '>') && str[i] != ' ')
		{
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
			continue ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**join_str(char **str_arr, char *str)
{
	int		i;
	char	**new_arr;

	new_arr = malloc(sizeof(char *) * (count_str(str_arr) + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (str_arr && str_arr[i])
	{
		new_arr[i] = ft_strdup(str_arr[i]);
		i++;
	}
	new_arr[i++] = ft_strdup(str);
	new_arr[i] = NULL;
	free_matrix(str_arr);
	return (new_arr);
}

char	*last_word(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '/')
			num = i;
		i++;
	}
	if (num != 0)
		num += 1;
	return (ft_strdup(str + num));
}

char	**new_args(char **str_arr, char *str)
{
	int		i;
	int		j;
	char	**new_arr;

	if (!str_arr && !str)
		return (NULL);
	new_arr = malloc(sizeof(char *) * (count_str(str_arr) + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	j = 0;
	if (str)
		new_arr[j++] = str;
	else
	{
		free(new_arr);
		return (NULL);
	}
	while (str_arr && str_arr[i])
		new_arr[j++] = ft_strdup(str_arr[i++]);
	new_arr[j] = NULL;
	return (new_arr);
}
