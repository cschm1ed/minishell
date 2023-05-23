/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:53:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/23 16:09:41 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void handle_duplications(t_data *pipex, t_list *parsed, t_info *info, int cnt);


int	ft_child_process(t_data *pipex, t_list *parsed, t_info *info, int cnt)
{
	t_parsed    *content;
	int         exit_builtin;

	content = lst_get_parsed(parsed);
	handle_files(pipex, parsed, info);
	handle_duplications(pipex, parsed, info, cnt);
	pipex->cmd_path = get_path(lst_get_parsed(parsed)->cmd, info);
	if (!pipex->cmd_path)
		execute_exit(info, NULL, 1);
	exit_builtin = execute_builtin_if(info, parsed, pipex, -1);
	if (exit_builtin != 1000)
		return (exit_builtin);
	if (execve(pipex->cmd_path, content->args, info->env) <= -1) 
		return (127);
	return (SUCCESS);
}

static void   handle_duplications(t_data *pipex, t_list *parsed, t_info *info, int cnt)
{
	t_parsed    *content;

	content = lst_get_parsed(parsed);
	if (parsed->next && content->redirect_output == NULL)
	{
		close(pipex->pipe_fd[cnt][0]);
		if (dup2(pipex->pipe_fd[cnt][1], STDOUT_FILENO) == -1)
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
	if (parsed != info->commands->parsed && !content->redirect_input)
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
}
