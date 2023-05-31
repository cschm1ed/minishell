/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:55:07 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/30 13:43:27 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_unset(t_info *info, char **arg, int fd_out)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (check_if_varname_is_valid(arg[i]) == FALSE)
			return (ft_printf("unset: `%s': not a valid identifier\n",
							fd_out, arg[i]), SUCCESS);
		ft_lstrmone((&info->env_lst), lst_find_node(info->env_lst, arg[i]),
			delete_variable);
		ft_lstrmone(&(info->export_lst), lst_find_node(info->export_lst,
				arg[i]), delete_variable);
		ft_lstrmone(&(info->user_vars), lst_find_node(info->user_vars, arg[i]),
			delete_variable);
		i ++;
	}
	return (SUCCESS);
}
