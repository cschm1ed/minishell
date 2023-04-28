/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:55:07 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 22:55:07 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_info *info, char **arg)
{
	t_list	*ptr;
	int 	i;

	i = 0;
	while (arg[i])
	{
		ptr = info->env_lst;
		while (ptr && ft_strncmp(((t_variable*)(ptr->content))->name,
								 arg[i], ft_strlen(arg[i]) + 1) != 0)
			ptr = ptr->next;
		ft_lstrmone(&(info->env_lst), ptr, delete_variable);
		i++;
	}
}
