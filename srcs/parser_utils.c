/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkieth <jkieth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:33:10 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/16 20:53:45 by jkieth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe(char *str, int *quotes, int word, int i)
{
	int	count_pipe;

	count_pipe = 0;
	while (str[++i])
	{
		if (isalpha(str[i]))
			word++;
		if (str[i] == 34)
			quotes[0]++;
		if (str[i] == 39)
			quotes[1]++;
		if (str[i] == '|' && amount_quotes(quotes) == 0)
		{
			if (word == 0)
				return (-1);
			count_pipe++;
			i++;
			while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
				i++;
			if (str[i] == '|' || str[i] == '\0')
				return (-1);
		}
	}
	return (count_pipe);
}

int	what_is_first(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34)
			return (34);
		if (str[i] == 39)
			return (39);
	}
	return (0);
}

int	check_quotes(char *str, int count1, int count2, int first_open)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 && str[i - 1] != 92)
		{
			count1++;
			if (count2 % 2 == 0)
				first_open = 1;
			if (count1 % 2 == 0 && first_open == 1)
				count2 = 0;
		}
		if (str[i] == 39 && str[i - 1] != 92)
		{
			count2++;
			if (count1 % 2 == 0)
				first_open = 2;
			if (count2 % 2 == 0 && first_open == 2)
				count1 = 0;
		}
	}
	if (count1 % 2 != 0 || count2 % 2 != 0)
		return (-1);
	return (count1 + count2);
}

char	*str_without_quotes(t_stct *data, char *str, int quote)
{
	char	*new_str;
	int		i;

	if (check_dollar(str) > 0)
		return (dollar(data, str));
	if (quote == 0)
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
		if (str[i] != quote)
			new_str = ft_charjoin(new_str, str[i]);
		i++;
	}
	free(str);
	return (new_str);
}

char	**arr_without_quotes(t_stct *data, char *str)
{
	int		first;
	int		i;
	char	**str_array;

	str_array = split_with_quotes(str, ' ');
	i = 0;
	while (str_array && str_array[i])
	{
		first = what_is_first(str_array[i]);
		str_array[i] = str_without_quotes(data, str_array[i], first);
		if (str_array[i] == NULL)
		{
			free_matrix(str_array);
			return (NULL);
		}
		i++;
	}
	return (str_array);
}
