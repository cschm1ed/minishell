/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:36:47 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 23:36:47 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Adds a list of variables to a linked list.
 *
 * @param list A pointer to a pointer to the head of the linked list.
 * @param arg An array of strings containing variable assignments in the format "name=value".
 *
 * @return SUCCESS if all variables are added successfully, or FAILURE if an error occurs.
 */
int	var_lst_add(t_list **list, char **arg)
{
	t_variable	*var;
	char		**split;
	int			i;

	i = 0;
	while (arg[i])
	{
		split = ft_split(arg[i], '=');
		if (!split)
			return (perror("malloc"), FAILURE);
		var = ft_calloc(sizeof(t_variable), 1);
		if (!var)
			return (perror("malloc"), FAILURE);
		var->name = ft_strdup(split[0]);
		var->value = ft_strdup(split[1]);
		ft_free_dbl_ptr(split);
		ft_lstadd_back(list, ft_lstnew((void *)(var)));
		i ++;
	}
	return (SUCCESS);
}
