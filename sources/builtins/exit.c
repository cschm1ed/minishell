/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:47:16 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/23 15:11:47 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_exit(t_info *info, char **arg, int exit_code)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (arg && arg[1] && arg[2])
	{
		ft_printf("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
		return (FAILURE);
	}
	if (arg && arg[1])
	{
		if (ft_strisnum(arg[1]) != 0
			&& !(*arg[1] == '-' && ft_strisnum(arg[1] + 1) == 0)
			&& arg[1][1] != 0)
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				STDERR_FILENO, arg[1]);
			exit_code = 255;
		}
		else
			exit_code = ft_atoi(arg[1]);
	}
	if (info)
		free_info(&info);
	exit(exit_code);
	return (exit_code);
}
