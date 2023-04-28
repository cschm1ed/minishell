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
	free(ptr->name);
	free(ptr->value);
	free(ptr);
}
