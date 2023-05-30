/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:53:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/30 13:05:20 by lspohle          ###   ########.fr       */
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
	int			exit_builtin;
	char		**env;

	content = setup(pipex, parsed, &info, cnt);
	exit_builtin = execute_builtin_if(info, parsed, pipex, -1);
	if (exit_builtin != 1000)
	{
		free_info(&info);
		exit (exit_builtin);
	}
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

	setup_signals_parent();
	content = lst_get_parsed(parsed);
	handle_files(pipex, parsed, (*info), cnt);
	dup_infiles(pipex, parsed, cnt);
	dup_outfiles(pipex, parsed, (*info), cnt);
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
	if (parsed != info->commands->parsed && !content->redirect_input)
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
