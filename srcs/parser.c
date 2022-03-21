/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:00:05 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/08 15:17:33 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(t_stct *data, char *str)
{
	int	count_pipe;

	count_pipe = check_pipe(str);
	if (count_pipe == -1)
	{
		data->exit_status = 1;
		ft_putendl_fd("minishell: syntax error with pipe", 2);
		free(str);
		return (1);
	}
	else if (count_pipe == 0)
		data->cmd = new_cmd(data, str);
	else if (count_pipe > 0)
		init_cmd(data, str);
	if (data->cmd == NULL)
	{
		free(str);
		return (1);
	}
	return (0);
}

void	*error_parse(t_stct *data, char *str, int num_error)
{
	if (num_error == 1)
	{
		data->exit_status = 1;
		ft_putendl_fd("minishell: syntax error with open quotes", 2);
	}
	else if (num_error == 2)
	{
		data->exit_status = 1;
		ft_putendl_fd("minishell: Error! Memory not allocated.", 2);
	}
	free(str);
	return (NULL);
}

char	**parse_string(t_stct *data, char *str)
{
	char	*new_str;
	char	**str_array;
	int		check;

	if (str[0] == '\0')
		return (NULL);
	new_str = ft_strtrim(str, " 	");
	check = check_quotes(new_str, 0, 0, 0);
	if (check == -1)
		return (error_parse(data, new_str, 1));
	else if (check > 0 || check_dollar(str) > 0)
		str_array = arr_without_quotes(data, new_str);
	else
		str_array = ft_split(new_str, ' ');
	if (!str_array)
		return (error_parse(data, new_str, 2));
	free(new_str);
	return (str_array);
}
