/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:54:18 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/24 18:38:29 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	execute_builtin(t_info *info,
				t_list *parsed, char *cmd, int fd_out);

int	execute_builtin_if(t_info *info, t_list *parsed, t_data *pipex, int cnt)
{
	char	*cmd;
	int		fd_out;
	int		exit_code;

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
	exit_code = execute_builtin(info, parsed, cmd, fd_out);
	if (exit_code == 1000)
		return (exit_code);
	if (parsed->next)
		close(pipex->pipe_fd[cnt][1]);
	return (exit_code);
}

static int	execute_builtin(t_info *info,
				t_list *parsed, char *cmd, int fd_out)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		exit_code = execute_echo(lst_get_parsed(parsed), fd_out);
	else if (ft_strcmp(cmd, "env") == 0)
		exit_code = execute_env(info, fd_out);
	else if (ft_strcmp(cmd, "exit") == 0)
		exit_code = execute_exit(info, lst_get_parsed(parsed)->args, 0);
	else if (ft_strcmp(cmd, "export") == 0)
		exit_code = execute_export(info, lst_get_parsed(parsed)->args, fd_out);
	else if (ft_strcmp(cmd, "pwd") == 0)
		exit_code = execute_pwd(info, fd_out);
	else if (ft_strcmp(cmd, "unset") == 0)
		exit_code = execute_unset(info, &lst_get_parsed(parsed)->args[1]);
	else if (ft_strcmp(cmd, "cd") == 0)
		exit_code = execute_cd(info, lst_get_parsed(parsed)->args[1]);
	else
		return (1000);
	return (exit_code);
}

int	execute_single(t_info *info, t_list *parsed, t_data *pipex)
{
	char	*cmd;

	cmd = lst_get_parsed(parsed)->cmd;
	if (cmd == NULL)
		return (FAILURE);
	if (ft_lstsize(parsed) != 1
		|| (ft_strcmp(cmd, "exit") != 0
			&& ft_strcmp(cmd, "echo") != 0
			&& ft_strcmp(cmd, "env") != 0
			&& ft_strcmp(cmd, "cd") != 0
			&& ft_strcmp(cmd, "export") != 0
			&& ft_strcmp(cmd, "pwd") != 0
			&& ft_strcmp(cmd, "unset") != 0))
		return (FAILURE);
	handle_files(pipex, parsed, info, 0);
	if (pipex->file_fd[0] >= 0 && pipex->file_fd[1] >= 0)
		g_exit_code = execute_builtin_if(info, parsed, pipex, 0);
	else
		g_exit_code = 127;
	return (SUCCESS);
}
