/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:00:05 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/17 21:59:52 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*alloc_cmd(t_stct *data, char *str)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->cmd = NULL;
	cmd->option = NULL;
	cmd->redir = NULL;
	cmd->heredoc_file = NULL;
	cmd->env = &data->env;
	cmd->exit_status = &data->exit_status;
	cmd->pid = -1;
	cmd->args = parse_string(data, str);
	free(str);
	if (!cmd->args)
		return (free_cmd(cmd));
	return (cmd);
}

t_cmd	*new_cmd(t_stct *data, char *str)
{
	t_cmd	*cmd;
	char	*new_str;
	int		check_redir;

	new_str = new_redirect_str(str, 0, 0);
	cmd = alloc_cmd(data, new_str);
	if (!cmd)
		return (NULL);
	check_redir = check_redirect(&cmd);
	if (check_redir == 1)
	{
		if (redirect(data, &cmd) == 1)
			return (free_cmd(cmd));
	}
	else if (check_redir == -1)
		return (free_cmd(cmd));
	else
	{
		cmd->cmd = ft_strdup(cmd->args[0]);
		cmd->cmd = find_path(cmd->cmd, data, 0);
		cmd->option = str_array_dup(cmd->args, 1, count_str(cmd->args));
	}
	return (cmd);
}

t_cmd	*cmd_last(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	cmd_addback(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!(*cmd))
		*cmd = new_cmd;
	else
	{
		tmp = cmd_last((*cmd));
		tmp->next = new_cmd;
		tmp->next->prev = tmp;
	}
}

void	init_cmd(t_stct *data, char *str)
{
	char	**str_array;
	int		i;

	str_array = ft_split(str, '|');
	if (!str_array)
		return ;
	i = 0;
	while (str_array[i])
	{
		if (i == 0)
			data->cmd = new_cmd(data, str_array[i]);
		else
			cmd_addback(&data->cmd, new_cmd(data, str_array[i]));
		i++;
	}
	free_matrix(str_array);
}
