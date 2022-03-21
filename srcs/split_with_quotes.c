/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:22:13 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/01 16:13:03 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_len(char *s, char c, char quote, int count_quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i])
			{
				if (s[i] == quote && s[i - 1] != 92)
					count_quote++;
				if (count_quote == 2)
					count_quote = 0;
				if (s[i] == c && count_quote != 1)
					break ;
				i++;
			}
		}
	}
	return (count);
}

char	**free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

char	**fill_str(char **str_array, char *str, char border, char quote)
{
	int	i[2];
	int	count;

	i[0] = 0;
	i[1] = 0;
	count = 0;
	while (str[i[1]])
	{
		if (str[i[1]] == quote && str[i[1] - 1] != 92)
			count++;
		if (count == 2)
			count = 0;
		if (str[i[1]] == border && count != 1)
		{
			while (str[i[1]] && str[i[1]] == border)
				i[1] += 1;
			i[0] += 1;
			continue ;
		}
		str_array[i[0]] = ft_charjoin(str_array[i[0]], str[i[1]]);
		if (!str_array[i[0]])
			return (free_array(str_array));
		i[1] += 1;
	}
	return (str_array);
}

char	**split_with_quotes(char *str, char border, char quote)
{
	char	**str_array;
	int		count;
	int		i;

	if (!str)
		return (NULL);
	count = ft_len(str, border, quote, 0);
	str_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str_array)
		return (NULL);
	i = 0;
	while (i < count + 1)
		str_array[i++] = NULL;
	str_array = fill_str(str_array, str, border, quote);
	if (!str_array)
		return (NULL);
	return (str_array);
}
