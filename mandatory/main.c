/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/01 18:22:00 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_iterate_through_cmds(t_data *pipex, char *cmd)
{
	ft_split_cmd_path(pipex, cmd);
	if (pipe(pipex->pipe_fd) == -1)
		exit_cmd_failed("pipe");
	pipex->pid = fork();
	if (pipex->pid == -1)
		exit_cmd_failed("fork");
	if (pipex->pid == 0)
		ft_child_process(pipex, cmd);
	else
		ft_parent_process(pipex);
	ft_free_dbl_ptr(pipex->cmd_split);
	free(pipex->cmd_path);
	pipex->cmd_path = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_data	pipex;

	pipex.envp = envp;
	ft_iterate_through_cmds(&pipex, "whoami");
	ft_iterate_through_cmds(&pipex, "hostname -s");
}
