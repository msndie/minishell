/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:45:11 by sclam             #+#    #+#             */
/*   Updated: 2022/03/21 16:40:53 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_exec(t_cmd *cmd, char **env)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		return (1);
	}
	g_stage = 1;
	if (cmd->pid == 0)
	{
		exec_redir(cmd);
		if (ft_exec_builtin(cmd) == 0)
			exit(*cmd->exit_status);
		execve(cmd->cmd, cmd->args, env);
		perror("execve");
		exit(errno);
	}
	return (0);
}

static void	status_define(t_stct *stct, int status)
{
	if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
		if (status == 131)
			ft_putstr_fd("Quit: 3\n", 2);
		else if (status == 130)
			ft_putchar_fd('\n', 2);
		stct->exit_status = status;
	}
	else
		stct->exit_status = status / 256;
	if (stct->exit_status == 2)
		stct->exit_status += 125;
}

static void	ft_wait(t_stct *stct, t_fd *fd_stct)
{
	t_cmd	*tmp;
	pid_t	pid;
	int		status;

	tmp = cmd_last(stct->cmd);
	while (tmp->prev != NULL && tmp->pid == -1)
		tmp = tmp->prev;
	pid = waitpid(tmp->pid, &status, 0);
	status_define(stct, status);
	ft_restore_fds(fd_stct);
	tmp = stct->cmd;
	while (tmp)
	{
		if (tmp->pid == pid || tmp->pid == -1)
		{
			tmp = tmp->next;
			continue ;
		}
		if (waitpid(tmp->pid, 0, WNOHANG) == 0)
		{
			kill(tmp->pid, SIGTERM);
			waitpid(tmp->pid, 0, 0);
		}
		tmp = tmp->next;
	}
}

static int	prepare(t_stct *stct, t_fd *fd_stct)
{
	t_cmd	*tmp;

	tmp = stct->cmd;
	ft_heredoc(tmp);
	if (g_stage == 228)
	{
		stct->exit_status = 1;
		return (1);
	}
	g_stage = 0;
	if (tmp && !tmp->next && !tmp->prev)
	{
		if (ft_check_one_cmd(fd_stct, stct))
			return (1);
	}
	return (0);
}

void	ft_exec_coms(t_stct *stct)
{
	int		fdpipe[2];
	t_fd	fd_stct;
	t_cmd	*tmp;
	char	**env;

	tmp = stct->cmd;
	if (prepare(stct, &fd_stct))
		return ;
	ft_save_first(&fd_stct);
	env = ft_env_to_arr(stct->env);
	if (!env)
		ft_putendl_fd("Malloc error while copying env\n", 2);
	while (tmp)
	{
		if (ft_save_sec(tmp, fdpipe, &fd_stct) == 1)
			break ;
		else if (ft_exec(tmp, env))
			break ;
		tmp = tmp->next;
	}
	ft_free_arr(env);
	ft_wait(stct, &fd_stct);
}
