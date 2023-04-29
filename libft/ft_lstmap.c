/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 19:42:45 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 17:13:32 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The function ft_lstmap() iterates the linked-list 'lst', and creates a new
// list resulting of the successive applications of the function 'f' to the
// content of each node.

#include "libft.h"

static t_list	*delete_node(t_list *node, t_list *head, void (*del)(void *))
{
	t_list	*tmp;

	while (head != node)
	{
		del(head->content);
		tmp = head;
		ft_lstdelone(head, del);
		head = tmp->next;
	}
	del(node->content);
	ft_lstdelone(node, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	if (!lst)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (!head)
	{
		del(head->content);
		ft_lstdelone(head, del);
		return (NULL);
	}
	lst = lst->next;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
			return (delete_node(node, head, del));
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}
