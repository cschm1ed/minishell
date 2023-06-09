/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:55:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/14 11:19:03 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_args(char **args, int j, int fd_out);
static int	ft_isoption(const char *args);

int	execute_echo(t_info *info, char **args, int fd_out)
{
	int		j;

	j = 1;
	if (!args[j])
		return (ft_putchar_fd('\n', fd_out), 0);
	if (ft_isoption(args[j]))
	{
		while (args[++j])
		{
			if (!ft_isoption(args[j]))
				break ;
		}
	}
	print_args(args, j, fd_out);
	if (!ft_isoption(args[1]))
		ft_putchar_fd('\n', fd_out);
	return ((void)info, 0);
}

static void	print_args(char **args, int j, int fd_out)
{
	while (args[j])
	{
		if (args[j][0] == 0)
			ft_putchar_fd(' ', fd_out);
		else
		{
			ft_putstr_fd(args[j], fd_out);
			if (args[j + 1] && args[j + 1][0])
				ft_putchar_fd(' ', fd_out);
		}
		j ++;
	}
}

static int	ft_isoption(const char *args)
{
	int	i;

	i = -1;
	if (args[++i] == '-')
	{
		while (args[++i])
			if (args[i] != 'n')
				return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
