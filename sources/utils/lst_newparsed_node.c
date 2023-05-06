/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_newparsed_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:46:28 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/06 13:46:28 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*lst_newparsed_node(void)
{
	t_parsed	*current;
	t_list		*node;

	current = ft_calloc(1, sizeof(t_parsed));
	if (current == NULL)
		return (perror("malloc"), NULL);
	node = ft_lstnew(current);
	if (node == NULL)
		return (free(current), perror("malloc"), NULL);
	node->content = (void *)current;
	return (node);
}
