/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/24 15:55:09 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	wait_for_children(t_data *pipex, int cnt, int status);
static int	create_pipes(t_data *pipex, t_list *parsed);

int	execute(t_info *info, t_list *parsed)
{
	t_data		*pipex;
	int			i;
	int			status;

	i = 0;
	pipex = info->pipex;
	if (create_pipes(pipex, parsed) == FAILURE)
		exit_error(info, __FILE__, __LINE__, "pipe");
	pipex->pid = ft_calloc(sizeof(pid_t), ft_lstsize(parsed));
	if (pipex->pid == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	if (execute_single(info, parsed, pipex) == SUCCESS)
		return (SUCCESS);
	while (parsed)
	{
		setup_signals_child();
		fork_process(info, pipex, parsed, i);
		i ++;
		parsed = parsed->next;
	}
	wait_for_children(pipex, i, status);
	setup_signals_parent();
	return (SUCCESS);
}

static int	create_pipes(t_data *pipex, t_list *parsed)
{
	int	amt;
	int	i;

	amt = ft_lstsize(parsed);
	pipex->pipe_fd = malloc(amt * sizeof(int *));
	i = 0;
	while (i < amt)
	{
		pipex->pipe_fd[i] = malloc(2 * sizeof(int));
		if (pipe(pipex->pipe_fd[i]) == -1)
			return (FAILURE);
		i ++;
	}
	return (SUCCESS);
}

static void	fork_process(t_info *info, t_data *pipex, t_parsed *parsed, int i)
{
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
		return (g_exit_code = 1, FAILURE);
	if (pipex->pid[i] == 0)
		ft_child_process(pipex, parsed, info, i);
	close(pipex->pipe_fd[i][1]);
}

static void	wait_for_children(t_data *pipex, int cnt, int status)
{
	int	j;

	j = 0;
	while (j <= cnt)
	{
		waitpid(pipex->pid[j], &status, 0);
		if ((((*(int *)&(status)) & 0177) == 0))
			g_exit_code = (((*(int *)&(status)) >> 8) & 0x000000ff);
		j ++;
	}
}
