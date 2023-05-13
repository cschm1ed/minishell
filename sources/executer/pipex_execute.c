/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:53:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/13 17:21:41 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// exectuable || builtin
int	ft_child_process(t_data *pipex, t_list *parsed, t_info *info)
{
	t_parsed  *content;
	int		  ret;
	
	content = lst_get_parsed(parsed);

	pipex->file_fd[1] = create_outfiles(parsed);
	pipex->file_fd[0] = check_infiles(parsed);
	if (pipex->file_fd[1] == STDOUT_FILENO && parsed->next)
	{
		close(pipex->pipe_fd[0]);
		printf(MAGENTA"Executing command: %s\n"ESC, lst_get_parsed(parsed)->cmd);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
		// write(1, "HELLO\n", 6);
	}
	if (pipex->file_fd[0] == STDIN_FILENO && parsed != info->commands->parsed)
	{
		close(pipex->pipe_fd[1]);
		printf(RED"Executing command: %s\n"ESC, lst_get_parsed(parsed)->cmd);
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		close(pipex->pipe_fd[0]);
	}
	// nur bei executable
	ret = execute_builtin_if(info, parsed);
	if (ret != 129)
		exit (ret);
	pipex->cmd_path = get_path(lst_get_parsed(parsed)->cmd, info);
	if (!pipex->cmd_path)
		return (FAILURE);
	if (execve(pipex->cmd_path, content->args, info->env) <= -1) 
		return (info->exit_code = 127, FAILURE);
}

void	ft_parent_process(t_data *pipex)
{
	// int		status;
	// int		exit_status;
	(void) pipex;
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
	// waitpid(pipex->pid, 0, WNOHANG);
	wait(NULL);
	// close(pipex->pipe_fd[1]);
	// dup2(pipex->pipe_fd[0], STDIN_FILENO);
	// close(pipex->pipe_fd[0]);
}
