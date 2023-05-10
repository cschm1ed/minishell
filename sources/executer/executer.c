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

typedef struct s_exec
{
    int     fd_in;
    int     fd_out;
    int     *pipes;
    t_list  *pids;
}   t_exec;

int executer(t_info *info)
{
	t_list	*parsed;
    t_exec  exec;

	return (SUCCESS);
}
