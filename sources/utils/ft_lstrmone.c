/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrmone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:02:58 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 23:02:58 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/**
 * Removes one node from a linked list and frees all its memory.
 *
 * @param head - head of the list from which the node should be deleted
 * @param node - pointer to the node to be deleted
 * @param del - function used to delete the content of the node
 */
void	ft_lstrmone(t_list **head, t_list *node, void (*del)(void*))
{
	t_list	*prev;
	t_list	*next;

	prev = *head;
	if (node == NULL)
		return ;
	if (*head == NULL)
		return ;
	if (node == *head)
	{
		*head = node->next;
		ft_lstdelone(node, del);
		return ;
	}
	while (prev && prev->next != node)
		prev = prev->next;
	if (prev == NULL)
		return ;
	next = prev->next->next;
	ft_lstdelone(node, del);
	prev->next = next;
}
