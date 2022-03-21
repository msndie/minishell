/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:32:54 by sclam             #+#    #+#             */
/*   Updated: 2022/03/21 16:40:50 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_ctrl_c(void)
{
	if (g_stage == 2)
	{
		rl_done = 1;
		g_stage = 228;
		return ;
	}
	if (g_stage == 1)
		return ;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_signals(int sig)
{
	if (sig == SIGINT)
		handle_ctrl_c();
	else if (sig == SIGQUIT)
		return ;
	else if (sig == SIGTERM)
		signal(SIGTERM, SIG_IGN);
}

void	ignore_signal_for_shell(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	signal(SIGTERM, handle_signals);
}
