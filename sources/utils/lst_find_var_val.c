/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_find_var_val.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:04:25 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/01 17:04:25 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Finds the value of a variable with a given name in a linked list.
 *
 * @param lst A pointer to the head of the linked list.
 * @param name The name of the variable to search for.
 *
 * @return A pointer to the value of the variable,
 * 								or NULL if the variable is not found.
 */
char	*lst_find_var_val(t_list *lst, char *name)
{
	if (lst_find_node(lst, name) != NULL)
		return (lst_get_var(lst_find_node(lst, name))->value);
	return (NULL);
}

t_list	*lst_find_node(t_list *lst, char *name)
{
	while (lst)
	{
		if (ft_strcmp(lst_get_var(lst)->name, name) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}