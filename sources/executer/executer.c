/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:42:15 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/03 19:15:28 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int executer(t_info *info)
{
	t_list	*parsed;

	parsed = info->commands->parsed;
	if (parsed->content == NULL)
		return (SUCCESS);
	while (parsed)
	{
		if (execute_builtin_if(info, parsed) == FAILURE)
			return (FAILURE);
		parsed = parsed->next;
	}
	return (SUCCESS);
}
