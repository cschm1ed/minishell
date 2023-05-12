/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:53:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/12 16:55:00 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_child_process(t_data *pipex, t_list *parsed, t_info *info)
{
	t_parsed  *content;
	
	content = lst_get_parsed(parsed);
	// dup2(pipex->file_fd[0], STDIN_FILENO);
	// close(pipex->file_fd[0]);
	// close(pipex->pipe_fd[0]);
	// dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	// close(pipex->pipe_fd[1]);
	// if (parsed == ft_lstlast(info->commands->parsed))
	// {
	// 	close(pipex->pipe_fd[1]);
	// 	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	// 	close(pipex->pipe_fd[0]);
	// 	dup2(pipex->file_fd[1], STDOUT_FILENO);
	// 	close(pipex->file_fd[1]);
	// }
	// print_lexed(content->args);
	if (execve(pipex->cmd_path, content->args, info->env) <= -1) 
		return (info->exit_code = 127, FAILURE);
}

void	ft_parent_process(t_data *pipex)
{
	// int		status;
	// int		exit_status;

	// if (waitpid(pipex->pid, &status, WNOHANG) == -1)
	// {
	// 	perror("waitpid: ");
	// 	exit(EXIT_FAILURE);
	// }
	// if (WIFEXITED(status))
	// {
	// 	exit_status = WEXITSTATUS(status);
	// 	if (exit_status == 2)
	// 		exit(exit_status);
	// }
	waitpid(pipex->pid, 0, WNOHANG);
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
}
