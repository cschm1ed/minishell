/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:54:18 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/14 12:16:01 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	execute_builtin(t_info *info,
				t_list *parsed, char *cmd, int fd_out);

/**
 * @brief if the given command is an executable it will be executed
 * @param info - info struct
 * @param parsed - parsed command info struct
 * @param pipex - pipex struct
 * @param cnt - position of command in list of commands
 * @return exit code if builtin, 1000 otherwise
 */
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

/**
 * Executes the specified built-in command.
 * @param info - info struct
 * @param parsed - parsed command info struct
 * @param cmd - command to execute
 * @param fd_out - output file descriptor
 * @return exit code of the executed command, 1000 if not found
 */
static int	execute_builtin(t_info *info,
								t_list *parsed, char *cmd, int fd_out)
{
	int	i;

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

/**
 * Executes a single command in the parent process if it is a builtin
 * @param info - info struct
 * @param parsed - parsed command info struct
 * @param pipex - pipex struct
 * @return SUCCESS if execution is successful, FAILURE otherwise
 */
int	execute_single(t_info *info, t_list *parsed, t_data *pipex)
{
	char	*cmd;
	int		i;
	int		flag;

	i = 0;
	flag = FALSE;
	cmd = lst_get_parsed(parsed)->cmd;
	if (cmd == NULL)
		return (FAILURE);
	while (info->builtins[i].command)
		if (ft_strcmp(info->builtins[i++].command, cmd) == 0)
			flag = TRUE;
	if (flag == FALSE || parsed->next)
		return (FAILURE);
	if (handle_files(pipex, parsed) == FAILURE)
		return (g_exit_code = 1, SUCCESS);
	if (pipex->file_fd[0] >= 0 && pipex->file_fd[1] >= 0)
		g_exit_code = execute_builtin_if(info, parsed, pipex, 0);
	else
		g_exit_code = 127;
	return (SUCCESS);
}
