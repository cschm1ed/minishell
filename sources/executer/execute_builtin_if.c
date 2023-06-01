/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:54:18 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/30 13:42:55 by lspohle          ###   ########.fr       */
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
		fd_out = 1;
	else if (parsed->next)
		fd_out = pipex->pipe_fd[cnt][1];
	else
		fd_out = pipex->file_fd[1];
	cmd = lst_get_parsed(parsed)->cmd;
	exit_code = execute_builtin(info, parsed, cmd, fd_out);
	if (exit_code == 1000)
		return (exit_code);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (exit_code);
}

static int	execute_builtin(t_info *info,
                              t_list *parsed, char *cmd, int fd_out)
{
	int i;

	i = 0;
	while (info->builtins[i].command)
	{
		if (ft_strcmp(info->builtins[i].command, cmd) == 0)
		{
			return (info->builtins[i].execute_function
					(info, lst_get_parsed(parsed)->args, fd_out));
		}
		i ++;
	}
	return (1000);
}

int	execute_single(t_info *info, t_list *parsed, t_data *pipex)
{
	char	*cmd;
	int     i;
	int     flag;

	i = 0;
	flag = FALSE;
	cmd = lst_get_parsed(parsed)->cmd;
	if (cmd == NULL)
		return (FAILURE);
	while (info->builtins[i].command)
		if (ft_strcmp(info->builtins[i++].command, cmd) == 0)
			flag = TRUE;
	if (ft_lstsize(parsed) != 1
		|| flag == FALSE)
		return (FAILURE);
	handle_files(pipex, parsed, info, 0);
	if (pipex->file_fd[0] >= 0 && pipex->file_fd[1] >= 0)
		g_exit_code = execute_builtin_if(info, parsed, pipex, 0);
	else
		g_exit_code = 127;
	return (SUCCESS);
}
