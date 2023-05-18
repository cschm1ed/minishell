/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:55:07 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 22:55:07 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int execute_unset(t_info *info, char **arg)
{
	int 	i;

	i = 0;
	while (arg[i])
	{
		ft_lstrmone((&info->env_lst), lst_find_node(info->env_lst, arg[i]),
					delete_variable);
		ft_lstrmone(&(info->export_lst), lst_find_node(info->export_lst, arg[i]),
					delete_variable);
		ft_lstrmone(&(info->user_vars), lst_find_node(info->user_vars, arg[i]),
					delete_variable);
		i ++;
	}
	return (SUCCESS);
}
