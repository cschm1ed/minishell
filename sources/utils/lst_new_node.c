/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:46:28 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/24 15:22:02 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Creates a t_list node and allocates memory for a t_paesed struct
 * as its content.
 *
 * @return - pointer to the created t_list node.
 */
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

/**
 * Creates a t_list node and allocates memory for a t_var struct
 * as its content. Assigns values to var.
 *
 * @param name - name assigned to new var
 * @param value - value assigned to new var
 * @return - pointer to new node
 */
t_list	*lst_newvar_node(char *name, char *value, int key)
{
	t_list		*node;
	t_variable	*var;

	var = malloc(sizeof(t_variable));
	if (var == NULL)
		return (NULL);
	var->name = name;
	var->value = value;
	var->key = key;
	node = ft_lstnew((void *)var);
	if (node == NULL)
		return (free(var), perror("malloc"), NULL);
	return (node);
}
