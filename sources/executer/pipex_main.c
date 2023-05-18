/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/13 17:53:07 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		return (info->exit_code = 1, FAILURE);
	i = 0;
	pipex->pid = ft_calloc(sizeof(pid_t), ft_lstsize(parsed));
	if (pipex->pid == NULL)
		return (perror("malloc"), FAILURE);
	if (ft_lstsize(parsed) == 1 && ft_strcmp(lst_get_parsed(parsed)->cmd, "exit") == 0)
		execute_exit(info);
	while (parsed)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (info->exit_code = 1, FAILURE);
		if (pipex->pid[i] == 0)
			ft_child_process(pipex, parsed, info, i);
		close(pipex->pipe_fd[i][1]);
		parsed = parsed->next;
		i ++;
	}
	j = 0;
	while (j++ <= i)
	{
		waitpid(pipex->pid[j], &status, 0);
		info->exit_code = status >> 8;
	}
	// free pipex
	return (SUCCESS);
}
