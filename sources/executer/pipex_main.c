/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/13 17:53:07 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute(t_info *info, t_list *parsed)
{
	t_data		pipex;

	while (parsed)
	{
		if (pipe(pipex.pipe_fd) == -1)
			return (info->exit_code = 1, FAILURE);
		pipex.pid = fork();
		if (pipex.pid == -1)
			return (info->exit_code = 1, FAILURE);
		if (pipex.pid == 0)
			ft_child_process(&pipex, parsed, info);
		ft_parent_process(&pipex);
		parsed = parsed->next;
	}
	return (SUCCESS);
}
