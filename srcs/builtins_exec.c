/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:41:51 by sclam             #+#    #+#             */
/*   Updated: 2022/03/17 22:22:51 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_builtin(t_cmd *cmd)
{
	int	ret;

	if (cmd->args)
	{
		if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
			ret = 1;
		else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
			ret = 1;
		else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
			ret = 1;
		else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
			ret = 1;
		else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
			ret = 1;
		else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
			ret = 1;
		else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
			ret = 1;
		else
			ret = 0;
		return (ret);
	}
	return (-1);
}

int	ft_exec_builtin(t_cmd *cmd)
{
	if (cmd->args)
	{
		if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
			ft_echo(cmd);
		else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
			ft_cd(cmd);
		else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
			ft_pwd(cmd);
		else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
			ft_export(cmd);
		else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
			ft_unset(cmd);
		else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
			ft_env(cmd);
		else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
			ft_exit(cmd);
		else
			return (1);
		return (0);
	}
	cmd->exit_status = 0;
	return (1);
}

static int	helper(t_fd *fd_stct, t_stct *stct)
{
	fd_stct->tmpin = dup(0);
	fd_stct->tmpout = dup(1);
	fd_stct->fdin = ft_open_infiles(stct->cmd);
	if (fd_stct->fdin == -1)
	{
		stct->exit_status = 1;
		return (1);
	}
	else if (fd_stct->fdin == -2)
		fd_stct->fdin = dup(fd_stct->tmpin);
	else
		dup2(fd_stct->fdin, 0);
	fd_stct->fdout = ft_open_outfiles(stct->cmd);
	if (fd_stct->fdout == -1)
	{
		stct->exit_status = 1;
		ft_restore_fds(fd_stct);
		close(fd_stct->fdin);
		return (1);
	}
	else if (fd_stct->fdout == -2)
		fd_stct->fdout = dup(fd_stct->tmpout);
	else if (fd_stct->fdout > 0)
		dup2(fd_stct->fdout, 1);
	return (0);
}

int	ft_check_one_cmd(t_fd *fd_stct, t_stct *stct)
{
	int	ret;

	ret = ft_check_builtin(stct->cmd);
	if (ret == 1 || ret == -1)
	{
		if (helper(fd_stct, stct))
			return (1);
		if (ret == 1)
			ft_exec_builtin(stct->cmd);
		ft_restore_fds(fd_stct);
		close(fd_stct->fdin);
		close(fd_stct->fdout);
		return (1);
	}
	else
		return (0);
}
