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

int execute_exit(t_info *info, char **arg, int exit_code)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (info)
		free_info(&info);
	if (arg && *arg)
	{
		if (ft_strisnum(*arg) != 0)
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", *arg);
			exit_code = 255;
		}
		else
			exit_code = ft_atoi(*arg);
	}
	exit(exit_code);
	return (exit_code);
}
