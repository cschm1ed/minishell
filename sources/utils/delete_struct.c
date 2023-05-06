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

void	delete_variable(void *content)
{
	t_variable	*ptr;

	ptr = (t_variable*)content;
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
		free(parsed->redirect_input);
	if (parsed->redirect_output)
		free(parsed->redirect_output);
	if (parsed->delimiter)
		free(parsed->delimiter);
	ft_bzero(content, sizeof(t_parsed));
}
