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

void	ft_lstrmone(t_list **head, t_list *node, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*prev;
	t_list	*next;

	prev = NULL;
	next = NULL;
	ptr = (*head)->next;
	if (!ptr)
	{
		free(*head);
		*head = NULL;
		return ;
	}
	prev = *head;
	while (ptr && ptr != node)
	{
		ptr = ptr->next;
		prev = prev->next;
	}
	next = ptr->next;
	del(ptr->content);
	free(ptr);
	ft_lstadd_back(&prev, next);
}
