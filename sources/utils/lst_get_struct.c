/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:05:15 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/29 15:07:37 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Returns a pointer to the variable contained in a
 * 										given node of a linked list.
 *
 * @param lst A pointer to the node in the linked list.
 *
 * @return A pointer to the variable contained in the node.
 */
t_variable	*lst_get_var(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	return ((t_variable *)(lst->content));
}

t_parsed	*lst_get_parsed(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	return ((t_parsed *)(lst->content));
}
