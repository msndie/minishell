/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:42:15 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/16 16:47:50 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*free_all(char **path_array, char *cmd_with_slash)
{
	if (path_array)
		free_matrix(path_array);
	if (cmd_with_slash)
		free(cmd_with_slash);
	return (NULL);
}

char	*find_path(char *cmd, t_stct *data, int i)
{
	t_node	*tmp;
	char	*path;
	char	**path_array;
	char	*cmd_with_slash;

	tmp = find_list_elem(data->env, "PATH");
	if (!tmp || !cmd)
		return (NULL);
	path = NULL;
	path_array = ft_split(tmp->info, ':');
	cmd_with_slash = ft_strjoin("/", cmd);
	while (cmd_with_slash && path_array && path_array[i])
	{
		path = ft_strjoin(path_array[i++], cmd_with_slash);
		if (access(path, F_OK) == 0 || !path)
			break ;
		free(path);
		path = NULL;
	}
	free_all(path_array, cmd_with_slash);
	if (path)
		free(cmd);
	else
		return (cmd);
	return (path);
}

int	count_str(char **strs)
{
	int	count;

	count = 0;
	if (!strs)
		return (count);
	while (strs[count])
		count++;
	return (count);
}

char	**str_array_dup(char **strs, int start, int finish)
{
	char	**new_str;
	int		i;

	i = 0;
	if (finish - start <= 0)
		return (NULL);
	new_str = malloc(sizeof(char *) * (finish - start) + 1);
	if (new_str == NULL)
		return (NULL);
	while (strs && strs[start] && start < finish)
	{
		new_str[i] = ft_strdup(strs[start]);
		start++;
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}

void	last_arg(t_stct *data)
{
	int	count;

	if ((*data).cmd->args)
	{
		if (ft_strncmp((*data).cmd->args[0], "echo", 5) == 0)
			return ;
		else
		{
			if ((*data).last_arg)
				free((*data).last_arg);
			count = count_str((*data).cmd->args) - 1;
			if (ft_strncmp((*data).cmd->args[count], "-", 1) == 0)
				(*data).last_arg = ft_strdup("");
			else if ((*data).cmd->args[count] != NULL)
				(*data).last_arg = ft_strdup((*data).cmd->args[count]);
			else
				(*data).last_arg = ft_strdup("");
		}
	}
	else
	{
		if ((*data).last_arg)
			free((*data).last_arg);
		(*data).last_arg = ft_strdup("");
	}
}
