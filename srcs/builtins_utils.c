/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:24:18 by sclam             #+#    #+#             */
/*   Updated: 2022/03/08 17:09:12 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_identif_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
			|| (i != 0 && !ft_isalpha(str[i]) && str[i] != '_'
				&& !ft_isdigit(str[i])))
		{
			ft_putstr_fd("usnet: ", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd(": not a valid identifier", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	ft_refresh_pwd(t_cmd *cmd)
{
	t_node	*tmp;

	tmp = *cmd->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 4) == 0)
		{
			free(tmp->info);
			tmp->info = NULL;
			tmp->info = getcwd(tmp->info, 0);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_lst_add_back(cmd->env, ft_lst_new());
		tmp = ft_lst_last(*cmd->env);
		tmp->name = ft_strdup("PWD");
		tmp->info = getcwd(tmp->info, 0);
	}
}

void	ft_refresh_oldpwd(char *info, t_cmd *cmd)
{
	t_node	*tmp;

	tmp = *cmd->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "OLDPWD", 6) == 0)
		{
			free(tmp->info);
			tmp->info = info;
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_lst_add_back(cmd->env, ft_lst_new());
		tmp = ft_lst_last(*cmd->env);
		tmp->name = ft_strdup("OLDPWD");
		tmp->info = info;
	}
}

void	ft_cd_home(t_cmd *cmd, char *info)
{
	t_node	*tmp;

	tmp = find_list_elem(*cmd->env, "HOME");
	if (tmp)
	{
		if (!tmp->info)
			tmp = NULL;
		else if (chdir(tmp->info) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			perror(tmp->info);
			*cmd->exit_status = 1;
			free(info);
			return ;
		}
	}
	if (!tmp)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		*cmd->exit_status = 1;
		free(info);
		return ;
	}
	ft_refresh_oldpwd(info, cmd);
	ft_refresh_pwd(cmd);
}
