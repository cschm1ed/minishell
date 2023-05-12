/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/12 15:35:04 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_iterate_through_cmds(t_data *pipex, t_list *parsed, t_info *info)
{
	int		i;

	i = 1;
	while (parsed)
	{
		// ft_split_cmd_path(pipex, i);
		pipex->cmd_path = get_path(lst_get_parsed(parsed)->cmd, info);
		if (pipe(pipex->pipe_fd) == -1)
			return (info->exit_code = 1, FAILURE);
		pipex->pid = fork();
		if (pipex->pid == -1)
			return (info->exit_code = 1, FAILURE);
		if (pipex->pid == 0)
			ft_child_process(pipex, parsed, info);
		else
			ft_parent_process(pipex);
		// ft_free_dbl_ptr(pipex->cmd_split);
		// free(pipex->cmd_path);
		// pipex->cmd_path = NULL;
		parsed = parsed->next;
	}
	if (pipex->file_fd[1] != STDOUT_FILENO)
		close (pipex->file_fd[1]);
}

int	pipex(t_info *info, t_list *parsed)
{
	t_data		pipex;
	t_parsed  *content;
	
	// print_lexed(lst_get_parsed(parsed)->args);
	content = lst_get_parsed(parsed);
	// redirect output
	if (content->redirect_output)
		pipex.file_fd[1] = open(lst_get_var(ft_lstlast(content->redirect_output))->value,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		pipex.file_fd[1] = STDOUT_FILENO;
	if (pipex.file_fd[1] == -1)
		return (FAILURE);
	// redirect input
	if (content->redirect_input)
		pipex.file_fd[0] = open(lst_get_var(ft_lstlast(content->redirect_input))->value, O_RDONLY);
	else
		pipex.file_fd[0] = STDIN_FILENO;
	if (pipex.file_fd[0] == -1)
		return (FAILURE);
	printf("In: %d\n", pipex.file_fd[0]);
	printf("Out: %d\n", pipex.file_fd[1]);
	
	ft_iterate_through_cmds(&pipex, parsed, info);
	if (pipex.file_fd[0] != STDIN_FILENO)
		close (pipex.file_fd[0]);
	// if (pipex.file_fd[1] != STDOUT_FILENO)
	// 	close (pipex.file_fd[1]);
	return (0);
}
