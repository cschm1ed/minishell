/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/12 16:57:42 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipex(t_info *info, t_list *parsed)
{
	t_data		pipex;
	t_parsed  *content;
	int		i;

	i = 1;
	while (parsed)
	{
		content = lst_get_parsed(parsed);
		pipex.file_fd[1] = create_outfiles(parsed);
		pipex.file_fd[0] = check_infiles(parsed);
		printf("In: %d\n", pipex.file_fd[0]);
		printf("Out: %d\n", pipex.file_fd[1]);
		pipex.cmd_path = get_path(lst_get_parsed(parsed)->cmd, info);
		if (!pipex.cmd_path)
			return (FAILURE);
		if (pipe(pipex.pipe_fd) == -1)
			return (info->exit_code = 1, FAILURE);
		pipex.pid = fork();
		if (pipex.pid == -1)
			return (info->exit_code = 1, FAILURE);
		if (pipex.pid == 0)
			ft_child_process(&pipex, parsed, info);
		else
			ft_parent_process(&pipex);
		// ft_free_dbl_ptr(pipex->cmd_split);
		// free(pipex->cmd_path);
		// pipex->cmd_path = NULL;
		parsed = parsed->next;
	}
	if (pipex.file_fd[0] != STDIN_FILENO)
		close (pipex.file_fd[0]);
	if (pipex.file_fd[1] != STDOUT_FILENO)
		close (pipex.file_fd[1]);
	return (3);
}

// int	pipex(t_info *info, t_list *parsed)
// {
// 	// t_data		pipex;
// 	// t_parsed  *content;
	
// 	// print_lexed(lst_get_parsed(parsed)->args);
// 	content = lst_get_parsed(parsed);
// 	pipex.file_fd[1] = create_outfiles(parsed);
// 	pipex.file_fd[0] = check_infiles(parsed);
// 	printf("In: %d\n", pipex.file_fd[0]);
// 	printf("Out: %d\n", pipex.file_fd[1]);
	
// 	// ft_iterate_through_cmds(&pipex, parsed, info);
// 	if (pipex.file_fd[0] != STDIN_FILENO)
// 		close (pipex.file_fd[0]);
// 	if (pipex.file_fd[1] != STDOUT_FILENO)
// 		close (pipex.file_fd[1]);
// 	return (0);
// }
