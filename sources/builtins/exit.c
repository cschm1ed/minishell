/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:47:16 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/01 15:21:23 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_strisnum(const char *str);

int	execute_exit(t_info *info, char **arg, int exit_code)
{
	if (info->pipex == NULL)
		ft_printf("exit\n", STDERR_FILENO);
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
    char	max[] = "9223372036854775807";
    char	min[] = "9223372036854775808";
    int		i;
    int		sign;

    i = 0;
    sign = 1;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i ++;
    }
    if (ft_strlen(str + i) < 19)
        return (0);
    if (ft_strlen(str + i) > 20)
        return (1);
    if (ft_strlen(str + i) == 20)
    {
        if (sign == 1 && ft_strcmp(str + i, max) < 0)
            return (FALSE);
        if (sign == -1 && ft_strcmp(str + i, min) < 0)
            return (FALSE);
    }
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return (FALSE);
        i ++;
    }
    return (TRUE);
}
