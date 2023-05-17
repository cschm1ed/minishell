/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:53:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/13 18:12:43 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_child_process(t_data *pipex, t_list *parsed, t_info *info, int cnt)
{
	t_parsed  *content;
	int		  ret;
	
	content = lst_get_parsed(parsed);
	if (content->redirect_output != STDOUT_FILENO)
		pipex->file_fd[1] = create_outfiles(parsed);
	if (content->redirect_input != STDIN_FILENO)
		pipex->file_fd[0] = check_infiles(parsed);
	if (parsed->next)
	{
		close(pipex->pipe_fd[cnt][0]);
		dup2(pipex->pipe_fd[cnt][1], STDOUT_FILENO);
		close(pipex->pipe_fd[cnt][1]);
	}
	else
	{
		close(pipex->pipe_fd[cnt][0]);
		close(pipex->pipe_fd[cnt][1]);
		dup2(pipex->file_fd[1], STDOUT_FILENO);
		if (pipex->file_fd[1] != STDOUT_FILENO)
			close(pipex->file_fd[1]);
	}
	if (parsed != info->commands->parsed)
	{
		close(pipex->pipe_fd[cnt][1]);
		dup2(pipex->pipe_fd[cnt - 1][0], STDIN_FILENO);
		close(pipex->pipe_fd[cnt][0]);
	}
	else
	{
		close(pipex->pipe_fd[cnt][0]);
		close(pipex->pipe_fd[cnt][1]);
		dup2(pipex->file_fd[0], STDIN_FILENO);
		if (pipex->file_fd[0] != STDIN_FILENO)
			close(pipex->file_fd[0]);
	}
	ret = execute_builtin_if(info, parsed);
	if (ret != 129)
		exit (ret);
	pipex->cmd_path = get_path(lst_get_parsed(parsed)->cmd, info);
	if (!pipex->cmd_path)
		return (FAILURE);
	if (execve(pipex->cmd_path, content->args, info->env) <= -1) 
		return (info->exit_code = 127, FAILURE);
}
