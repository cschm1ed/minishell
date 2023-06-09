/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:53:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/14 13:04:00 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		dup_infiles(t_data *pipex, t_list *parsed, int cnt);
static void		dup_outfiles(t_data *pipex, t_list *parsed,
					t_info *info, int cnt);
static t_parsed	*setup(t_data *pipex, t_list *parsed, t_info **info, int cnt);

int	ft_child_process(t_data *pipex, t_list *parsed, t_info *info, int cnt)
{
	t_parsed	*content;
	char		**env;

	content = setup(pipex, parsed, &info, cnt);
	if (content == NULL)
		execute_exit_child(info, NULL, 1);
	close_pipes(&pipex);
	env = env_to_arr(info);
	if (env == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	if (execve(pipex->cmd_path, content->args, env) <= -1)
		exit (127);
	exit (SUCCESS);
}

static t_parsed	*setup(t_data *pipex, t_list *parsed, t_info **info, int cnt)
{
	t_parsed	*content;
	int			exit_builtin;

	setup_signals(keybindings_child);
	content = lst_get_parsed(parsed);
	if (handle_files(pipex, parsed) == FAILURE)
		return (NULL);
	dup_infiles(pipex, parsed, cnt);
	dup_outfiles(pipex, parsed, (*info), cnt);
	exit_builtin = execute_builtin_if(*info, parsed, pipex, -1);
	if (exit_builtin != 1000)
	{
		free_info(info);
		exit (exit_builtin);
	}
	pipex->cmd_path = get_path(lst_get_parsed(parsed)->cmd, (*info));
	if (!pipex->cmd_path)
	{
		free_info(info);
		exit(g_exit_code);
	}
	return (content);
}

static void	dup_outfiles( t_data *pipex, t_list *parsed, t_info *info, int cnt)
{
	t_parsed	*content;

	content = lst_get_parsed(parsed);
	if (parsed != info->commands->parsed
		&& !content->redirect_input && lst_get_parsed(parsed)->hdoc == FALSE)
	{
		dup2(pipex->pipe_fd[cnt - 1][0], STDIN_FILENO);
		if (pipex->pipe_fd[cnt - 1][0] != STDIN_FILENO)
			close(pipex->pipe_fd[cnt - 1][0]);
	}
	else if (pipex->file_fd[0] != STDIN_FILENO)
	{
		dup2(pipex->file_fd[0], STDIN_FILENO);
		close(pipex->file_fd[0]);
	}
}

static void	dup_infiles(t_data *pipex, t_list *parsed, int cnt)
{
	t_parsed	*content;

	content = lst_get_parsed(parsed);
	if (parsed->next && content->redirect_output == NULL)
	{
		dup2(pipex->pipe_fd[cnt][1], STDOUT_FILENO);
		close(pipex->pipe_fd[cnt][1]);
	}
	else
	{
		close(pipex->pipe_fd[cnt][1]);
		if (pipex->file_fd[1] != STDOUT_FILENO)
		{
			dup2(pipex->file_fd[1], STDOUT_FILENO);
			close(pipex->file_fd[1]);
		}
	}
}
