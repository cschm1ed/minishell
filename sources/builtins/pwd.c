/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:35:51 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/03 19:26:05 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute_pwd(t_info *info)
{
	t_list	*ptr;

	ptr = info->env_lst;
	while (ptr && ft_strncmp(ptr->content, "PWD=", 4))
	{
		//printf(MAGENTA"Content: %s\n"ESC, ptr->content);
		ptr = ptr->next;
	}	
    printf("%s\n", ptr->content + 4);
	// printf("%s\n", *envp + 4);
}
