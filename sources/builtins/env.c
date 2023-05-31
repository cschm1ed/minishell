/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:03:58 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/31 15:52:35 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_var_lst(t_list *lst, int fd_out);

int	execute_env(t_info *info, int fd_out, char **args)
{
	int	i;

	i = 1;
	if (args[1])
	{
		while (args[i])
		{
			if (ft_strcmp(args[i], "env") != 0)
			{
				ft_putstr_fd("env: ", fd_out);
				ft_putstr_fd(args[i], fd_out);
				ft_putstr_fd(": No such file or directory\n", fd_out);
				return (g_exit_code = 127, 127);
			}
				i ++;
		}
	}
	print_var_lst(info->env_lst, fd_out);
	ft_putstr_fd("_=/Users/cschmied/Documents/", fd_out);
	ft_putstr_fd("minishell/sources/builtins/env.c\n", fd_out);
	return (0);
}

static void	print_var_lst(t_list *lst, int fd_out)
{
	while (lst)
	{
		ft_putstr_fd(lst_get_var(lst)->name, fd_out);
		ft_putchar_fd('=', fd_out);
		ft_putstr_fd(lst_get_var(lst)->value, fd_out);
		ft_putchar_fd('\n', fd_out);
		lst = lst->next;
	}
}
