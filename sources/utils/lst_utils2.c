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

#include <minishell.h>

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

int	lst_replace_var_val(t_list *list, char *name, char *new)
{
	char	*replacement;

	replacement = ft_strdup(new);
	if (replacement == NULL)
		return (perror("malloc"), FAILURE);
	if (lst_find_node(list, name) != NULL)
		lst_get_var(lst_find_node(list, name))->value = replacement;
	else
		free(replacement);
	return (SUCCESS);
}

/**
 * returns the value of the variable searched for by looking through
 * the env_lst and user_vars list.
 *
 * @param info - general info struct
 * @param name - name of the variable whose value is sought
 * @return
 */
char	*lsts_find_var_val(t_info *info, char *name)
{
	if (lst_find_var_val(info->env_lst, name))
		return (lst_find_var_val(info->env_lst, name));
	if (lst_find_var_val(info->export_lst, name))
		return (lst_find_var_val(info->export_lst, name));
	else
		return (lst_find_var_val(info->user_vars, name));
}

void	ft_lstrmone(t_list **head, t_list *node, void (*del)(void*))
{
	t_list	*prev;
	t_list	*curr;

	if (!node || !(*head))
		return ;
	if (node == *head)
	{
		*head = node->next;
		ft_lstdelone(node, del);
		return ;
	}
	prev = *head;
	curr = (*head)->next;
	while (curr)
	{
		if (curr == node)
		{
			prev->next = curr->next;
			ft_lstdelone(curr, del);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
