/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strr_arr_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:11:44 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/01 19:11:44 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Converts a null-terminated array of strings into a linked list.
 *
 * @param arr A null-terminated array of strings.
 *
 * @return A pointer to the head of the linked list,
 * 										or NULL if an error occurs.
 */
t_list	*str_arr_to_lst(char **arr)
{
	int 	i;
	t_list	*new_lst;
	t_list	*new_node;

	i = 0;
	while (arr[i])
	{
		new_node = ft_lstnew((void*)arr[i]);
		if (!new_node)
			return (perror("malloc"), NULL);
		ft_lstadd_back(&new_lst, new_node);
		i ++;
	}
	return (new_lst);
}
