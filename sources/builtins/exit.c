/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:47:16 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/01 14:45:39 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_strisnum(const char *str);

int	execute_exit(t_info *info, char **arg, int exit_code)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (arg && arg[1])
	{
		if (ft_strisnum(arg[1]) != 0)
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				STDERR_FILENO, arg[1]);
			exit(255);
		}
	}
	if (arg && arg[1] && arg[2])
	{
		ft_printf("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
		return (FAILURE);
	}
	exit_code = ft_atoi(arg[1]);
	if (info)
		free_info(&info);
	exit(exit_code);
	return (exit_code);
}

static int	ft_strisnum(const char *str)
{
	char		max[] = "9223372036854775807";
	int			i;
	int			j;

	j = 0;
	i = 0;
	while (ft_isspace(str[j]) || str[i] == '-' || str[i] == '+')
		j ++;
	if (ft_strlen(str + j) > 19)
		return (1);
	else if (ft_strlen(str + j) == 19)
	{
		while (str[i + j])
		{
			if (str[i + j] > max[i])
				if (str[j] != '-' || str[18] >= '8')
					return (1);
			i ++;
		}
	}
	i = 0;
	while (str[i + j])
	{
		if (ft_isdigit(str[i + j]) == 0)
			return (1);
		i ++;
	}
	return (0);
}
