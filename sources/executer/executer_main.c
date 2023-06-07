/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/07 17:30:43 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	wait_for_children(t_data *pipex, int cnt);
static int	create_pipes(t_data *pipex, t_list *parsed);
static void	fork_process(t_info *info, t_data *pipex, t_list *parsed, int i);

/**
 * @brief execute command by command
 * 
 * @param info - info struct with all neccessary info (commands, etc.)
 * @param parsed - list of parsed struct
 * @return int - failure or success
 */
int	execute(t_info *info, t_list *parsed)
{
	t_data		*pipex;
	int			i;

	i = 0;
	info->pipex = ft_calloc(sizeof(t_data), 1);
	pipex = info->pipex;
	pipex->pid = ft_calloc(sizeof(pid_t), ft_lstsize(parsed) + 1);
	if (pipex->pid == NULL || create_pipes(pipex, parsed) == FAILURE
		|| pipex == NULL)
		exit_error(info, __FILE__, __LINE__, "pipe or malloc");
	if (execute_single(info, parsed, pipex) == SUCCESS)
		return (free_pipex(&info->pipex), SUCCESS);
	while (parsed)
	{
		setup_signals(keybindings_child);
		fork_process(info, pipex, parsed, i++);
		parsed = parsed->next;
	}
	wait_for_children(pipex, i);
	setup_signals(keybindings_parent);
	return (free_pipex(&info->pipex), SUCCESS);
}

/**
 * @brief creates a pipe for every command (node)
 * 
 * @param pipex - data struct with execution info (command path, pipe, pid, ...)
 * @param parsed - list of parsed struct
 * @return int - failure or success
 */
static int	create_pipes(t_data *pipex, t_list *parsed)
{
	int	amt;
	int	i;

	i = 0;
	amt = ft_lstsize(parsed);
	pipex->pipe_fd = ft_calloc(amt + 1, sizeof(int *));
	while (i < amt)
	{
		pipex->pipe_fd[i] = ft_calloc(2, sizeof(int));
		if (pipex->pipe_fd[i] == NULL
			|| pipe(pipex->pipe_fd[i]) == -1)
			return (FAILURE);
		i ++;
	}
	return (SUCCESS);
}

/**
 * @brief forks to execute the command currently looked at
 * 
 * @param info - info struct with all neccessary info (commands, ...)
 * @param pipex - data struct with execution info (command path, pipe, pid, ...)
 * @param parsed - list of parsed struct
 * @param i - current command
 */
static void	fork_process(t_info *info, t_data *pipex, t_list *parsed, int i)
{
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
	{
		g_exit_code = 1;
		exit_error(info, __FILE__, __LINE__, "fork");
	}
	if (pipex->pid[i] == 0)
		ft_child_process(pipex, parsed, info, i);
	close(pipex->pipe_fd[i][1]);
}

/**
 * @brief waits for child processes to finish
 * 
 * @param pipex - data struct with execution info (command path, pipe, pid, ...)
 * @param cnt - amount of commands (nodes)
 */
static void	wait_for_children(t_data *pipex, int cnt)
{
	int	j;
	int	status;

	status = 0;
	j = 0;
	while (j <= cnt)
	{
		waitpid(pipex->pid[j], &status, 0);
		if ((((*(int *)&(status)) & 0177) == 0))
			g_exit_code = (((*(int *)&(status)) >> 8) & 0x000000ff);
		j ++;
	}
}
