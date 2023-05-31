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

int	execute_env(t_info *info, int fd_out, char **args)
{
	int	i;
	t_list  *lst;

	i = 1;
	lst = info->env_lst;
	if (args[1])
	{
		while (args[i])
		{
			if (ft_strcmp(args[i], "env") != 0)
			{
				ft_printf("env: %s: No such file or directory\n",
						fd_out, args[i]);
				return (g_exit_code = 127, 127);
			}
				i ++;
		}
	}
	while (lst)
	{
		ft_printf("%s=%s\n", fd_out,
		          lst_get_var(lst)->name, lst_get_var(lst)->value);
		lst = lst->next;
	}
	ft_printf("_=/Users/cschmied/Documents/minishell/sources/builtins/env.c\n",
			    fd_out);
	return (0);
}
