/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/13 17:14:50 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute(t_info *info, t_list *parsed)
{
	t_data		pipex;

	while (parsed)
	{
		printf(GREEN"Executing command: %s\n"ESC, lst_get_parsed(parsed)->cmd);
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

// int	pipex(t_info *info, t_list *parsed)
// {
// 	t_data		pipex;
// 	t_parsed  *content;
// 	int		i;

// 	i = 1;
// 	while (parsed)
// 	{
// 		content = lst_get_parsed(parsed);
// 		pipex.cmd_path = get_path(lst_get_parsed(parsed)->cmd, info);
// 		if (!pipex.cmd_path)
// 			return (FAILURE);
// 		if (pipe(pipex.pipe_fd) == -1)
// 			return (info->exit_code = 1, FAILURE);
// 		pipex.pid = fork();
// 		if (pipex.pid == -1)
// 			return (info->exit_code = 1, FAILURE);
// 		if (pipex.pid == 0)
// 			ft_child_process(&pipex, parsed, info);
// 		ft_parent_process(&pipex);
// 		// ft_free_dbl_ptr(pipex->cmd_split);
// 		// free(pipex->cmd_path);
// 		// pipex->cmd_path = NULL;
		
// 	}
// 	return (3);
// }
