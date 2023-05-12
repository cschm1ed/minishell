/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delet_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:19:28 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 23:19:28 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * frees all memory, a s_variable struct holds.
 *
 * @param content pointer to the struct to be deleted.
 */
void	delete_variable(void *content)
{
	t_variable	*ptr;

	ptr = (t_variable *)content;
	if (ptr == NULL)
		return ;
	if (ptr->name)
	{
		free(ptr->name);
		ptr->name = NULL;
	}
	if (ptr->value)
	{
		free(ptr->value);
		ptr->value = NULL;
	}
	free(ptr);
}

/**
 * frees all memory held by a s_parsed struct.
 *
 * @param content - pointer to the struct to be freed
 */
void	delete_parsed(void *content)
{
	t_parsed	*parsed;

	parsed = (t_parsed *)content;
	if (parsed == NULL)
		return ;
	if (parsed->cmd)
		free(parsed->cmd);
	if (parsed->args)
		ft_free_dbl_ptr(parsed->args);
	if (parsed->redirect_input)
		ft_lstclear(&(parsed->redirect_input), delete_variable);
	if (parsed->redirect_output)
		ft_lstclear(&(parsed->redirect_output), delete_variable);
	ft_bzero(content, sizeof(t_parsed));
}
