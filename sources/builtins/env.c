/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:03:58 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/14 09:51:49 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_env(t_info *info, char **args, int fd_out)
{
	t_list	*lst;
	int		i;

	lst = info->env_lst;
	i = 0;
	if (args[1])
	{
		while (args[++i])
		{
			if (ft_strcmp(args[i], "env") != 0)
				return (ft_printf("env: %s: No such file or directory\n",
						fd_out, args[i]), g_exit_code = 127, 127);
		}
	}
	while (lst)
	{
		ft_printf("%s=%s\n", fd_out,
			lst_get_var(lst)->name, lst_get_var(lst)->value);
		lst = lst->next;
	}
	return (0);
}
