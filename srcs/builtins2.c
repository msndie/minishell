/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:31:17 by sclam             #+#    #+#             */
/*   Updated: 2022/03/20 16:42:46 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_cmd *cmd)
{
	char	*info;

	info = NULL;
	info = getcwd(info, 0);
	*cmd->exit_status = 0;
	if (cmd->args[1])
	{
		if (cmd->args[1][0] == '\0')
			return ;
		if (chdir(cmd->args[1]) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			perror(cmd->args[1]);
			*cmd->exit_status = 1;
			free(info);
		}
		else
		{
			ft_refresh_oldpwd(info, cmd);
			ft_refresh_pwd(cmd);
		}
	}
	else
		ft_cd_home(cmd, info);
}

void	ft_pwd(t_cmd *cmd)
{
	char	*str;

	str = NULL;
	str = getcwd(str, 0);
	ft_putendl_fd(str, 1);
	free(str);
	*cmd->exit_status = 0;
}

void	ft_export(t_cmd *cmd)
{
	int		i;

	i = 1;
	*cmd->exit_status = 0;
	if (cmd->args[i])
	{
		while (cmd->args[i])
		{
			ft_add_idtf(cmd->args[i], ft_check_idtf(cmd->args[i], cmd), cmd);
			i++;
		}
		return ;
	}
	ft_print_export(cmd);
}
