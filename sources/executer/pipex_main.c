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

#include "../../includes/minishell.h"

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
	t_data		pipex;
	int			i;

	if (create_pipes(&pipex, parsed) == FAILURE)
		return (info->exit_code = 1, FAILURE);
	i = -1;
	while (parsed)
	{
		++i;
		pipex.pid = fork();
		if (pipex.pid == -1)
			return (info->exit_code = 1, FAILURE);
		if (pipex.pid == 0)
			ft_child_process(&pipex, parsed, info, i);
		close(pipex.pipe_fd[i][1]);
		parsed = parsed->next;
	}
	while (waitpid(-1, 0, 0) != -1)
		;
	return (SUCCESS);
}
