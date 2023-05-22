/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:55:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/16 15:20:07 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void print_args(char **args, int j, int fd_out);
static int	ft_isoption(const char *args);

int execute_echo(t_parsed *parsed, int fd_out)
{
	char	**args;
	int		j;

	args = parsed->args;
	j = 0;
	if (ft_isoption(args[j]))
		while (args[++j])
		{
			if (!ft_isoption(args[j]))
				break;
		}
	print_args(args, j, fd_out);
	if (!ft_isoption(args[0]))
		ft_putchar_fd('\n', fd_out);
	return (0);
}

static void print_args(char **args, int j, int fd_out)
{
	j++;
	while (args[j])
	{
		ft_putstr_fd(args[j], fd_out);
		if (args[++j])
			ft_putstr_fd(" ", fd_out);
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
