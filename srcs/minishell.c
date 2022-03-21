/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:00:05 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/21 16:38:00 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	change_under_dash(t_node *node)
{
	t_node	*tmp;

	tmp = find_list_elem(node, "_");
	if (tmp)
	{
		if (tmp->info)
			free(tmp->info);
		tmp->info = ft_strdup("/usr/bin/env");
	}
}

static int	str_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 33 && str[i] <= 126)
			return (1);
		i++;
	}
	free(str);
	return (0);
}

static void	init(t_stct *stct, char **env)
{
	rl_catch_signals = 0;
	env_lists(stct, env, 0);
	increment_lvl(stct->env);
	change_under_dash(stct->env);
	stct->exit_status = 0;
	stct->last_arg = NULL;
	g_stage = 0;
	ignore_signal_for_shell();
}

static int	str_check(char	*str, t_stct *stct)
{
	if (!str)
	{
		ft_putstr_fd("exit\n", 2);
		exit(stct->exit_status);
	}
	if (str_is_empty(str) == 0)
		return (1);
	add_history(str);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_stct	data;
	char	*str;

	(void)argc;
	(void)argv;
	init(&data, env);
	while (1)
	{
		g_stage = 0;
		str = readline("minishell$> ");
		if (str_check(str, &data))
			continue ;
		if (parser(&data, str))
			continue ;
		ft_exec_coms(&data);
		last_arg(&data);
		ft_free_stcs(&data);
		free(str);
	}
}
