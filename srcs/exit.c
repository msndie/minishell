/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:35:33 by sclam             #+#    #+#             */
/*   Updated: 2022/03/13 17:33:50 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_overflow(unsigned long result, int m)
{
	int	ret;

	ret = 0;
	if (m == -1)
	{
		if (result > ULONG_MAX / 2UL + 1UL)
			ret = -1;
	}
	else
	{
		if (result > LONG_MAX)
			ret = -1;
	}
	return (ret);
}

static long	ft_atoi_for_exit(const char *str, int *flag)
{
	int				m;
	unsigned long	result;

	result = 0;
	m = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m = -1;
		str++;
		if (*str == '-' || *str == '+')
			*flag = 1;
	}
	if (ft_strlen(str) > 19 || ft_strlen(str) == 0)
		*flag = 1;
	while (*str <= '9' && *str >= '0')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0' || ft_check_overflow(result, m) == -1)
		*flag = 1;
	return ((long)result * m);
}

static void	check_error(int flag, t_cmd *cmd, int i)
{
	if (flag == 1)
	{
		ft_putstr_fd("exit\nexit: ", 2);
		ft_putstr_fd(cmd->args[i], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
}

void	ft_exit(t_cmd *cmd)
{
	int				i;
	int				flag;
	unsigned char	status;

	i = 1;
	flag = 0;
	status = 0;
	while (cmd->args && cmd->args[i])
	{
		if (i > 1)
		{
			ft_putstr_fd("exit\nexit: too many arguments\n", 2);
			*cmd->exit_status = 1;
			return ;
		}
		status = (unsigned char)ft_atoi_for_exit(cmd->args[i], &flag);
		check_error(flag, cmd, i);
		i++;
	}
	ft_putstr_fd("exit\n", 2);
	if (i == 1)
		status = *cmd->exit_status;
	exit((int)status);
}
