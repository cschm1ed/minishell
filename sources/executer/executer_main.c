/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/23 16:03:39 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int execute_single(t_info *info, t_list *parsed, t_data *pipex);

static int	create_pipes(t_data *pipex, t_list *parsed)
{
	int	amt;
	int i;

	amt = ft_lstsize(parsed);
	pipex->pipe_fd = malloc(amt * sizeof(int *));
	i = -1;
	while (++i < amt)
	{
		pipex->pipe_fd[i] = malloc(2 * sizeof(int));
		if (pipe(pipex->pipe_fd[i]) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}

int execute(t_info *info, t_list *parsed)
{
	t_data		*pipex;
	int			i;
	int 		j;
	int			status;

	pipex = info->pipex;
	if (create_pipes(pipex, parsed) == FAILURE)
		exit_error(info, __FILE__, __LINE__, "pipe");
	i = 0;
	pipex->pid = ft_calloc(sizeof(pid_t), ft_lstsize(parsed));
	if (pipex->pid == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	if (execute_single(info, parsed, pipex) == SUCCESS)
		return (SUCCESS);
	while (parsed)
	{
		setup_signals_child();
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (g_exit_code = 1, FAILURE);
		if (pipex->pid[i] == 0)
			ft_child_process(pipex, parsed, info, i);
		setup_signals_parent();
		close(pipex->pipe_fd[i][1]);
		i ++;
		parsed = parsed->next;
	}
	j = 0;
	while (j <= i)
	{
		waitpid(pipex->pid[j], &status, 0);
		if ((((*(int *)&(status)) & 0177) == 0))
			g_exit_code = (((*(int *)&(status)) >> 8) & 0x000000ff);
		j ++;
	}
	return (SUCCESS);
}

static int execute_single(t_info *info, t_list *parsed, t_data *pipex)
{
	char *cmd;

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

void handle_files(t_data *pipex, t_list *parsed, t_info *info, int cnt)
{
	pipex->file_fd[0] = check_infiles(parsed, cnt, pipex);
	if (pipex->file_fd[0] == -1 && parsed->next == NULL)
		execute_exit(info, NULL, 1);
	pipex->file_fd[1] = create_outfiles(parsed);
	if (pipex->file_fd[1] == -1)
		execute_exit(info, NULL, 1);
}
