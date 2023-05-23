/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:54:18 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/23 15:52:35 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int  execute_builtin_if(t_info *info, t_list *parsed, t_data *pipex, int cnt)
{
	char	*cmd;
	int     fd_out;

	if (cnt == -1)
		fd_out = STDOUT_FILENO;
	else if (parsed->next)
	{
		fd_out = pipex->pipe_fd[cnt][1];
		ft_printf("next is %d\n", fd_out);
	}
	else
		fd_out = pipex->file_fd[1];
	cmd = lst_get_parsed(parsed)->cmd;
	if (ft_strcmp(cmd, "echo") == 0)
		info->exit_code = execute_echo(lst_get_parsed(parsed), fd_out);
	else if (ft_strcmp(cmd, "env") == 0)
		info->exit_code = execute_env(info, fd_out);
	else if (ft_strcmp(cmd, "exit") == 0)
		info->exit_code = execute_exit(info, &lst_get_parsed(parsed)->args[1], 0);
	else if (ft_strcmp(cmd, "export") == 0)
		info->exit_code = execute_export(info, lst_get_parsed(parsed)->args, fd_out);
	else if (ft_strcmp(cmd, "pwd") == 0)
		info->exit_code = execute_pwd(info, fd_out);
	else if (ft_strcmp(cmd, "unset") == 0)
		info->exit_code = execute_unset(info, &lst_get_parsed(parsed)->args[1]);
	else if (ft_strcmp(cmd, "cd") == 0)
		info->exit_code = execute_cd(info, lst_get_parsed(parsed)->args[1]);
	else
		return (1000);
	if (parsed->next)
		close(pipex->pipe_fd[cnt][1]);
	return (info->exit_code);
}
