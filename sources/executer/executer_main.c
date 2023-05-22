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

static int execute_single(t_info *info, t_list *parsed, const t_data *pipex);
static void handle_files(t_data *pipex, t_list *parsed, t_info *info);

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
	int         builtin_return;
	int			status;

	pipex = info->pipex;
	if (create_pipes(pipex, parsed) == FAILURE)
		return (info->exit_code = 1, FAILURE);
	i = 0;
	pipex->pid = ft_calloc(sizeof(pid_t), ft_lstsize(parsed));
	if (pipex->pid == NULL)
		return (perror("malloc"), FAILURE);
	if (execute_single(info, parsed, pipex) == SUCCESS)
		return (SUCCESS);
	while (parsed)
	{
		handle_files(pipex, parsed, info);
		builtin_return = execute_builtin_if(info, parsed, pipex);
		if (builtin_return != 129)
			info->exit_code = builtin_return;
		else
		{
			pipex->pid[i] = fork();
			if (pipex->pid[i] == -1)
				return (info->exit_code = 1, FAILURE);
			if (pipex->pid[i] == 0)
				ft_child_process(pipex, parsed, info, i);
			close(pipex->pipe_fd[i][1]);
		}
		parsed = parsed->next;
		i ++;
	}
	j = 0;
	while (j++ <= i)
	{
		waitpid(pipex->pid[j], &status, 0);
		info->exit_code = status >> 8;
	}
	return (SUCCESS);
}

static int execute_single(t_info *info, t_list *parsed, const t_data *pipex)
{
	char *cmd;

	cmd = lst_get_parsed(parsed)->cmd;
	if (cmd == NULL)
		return (FAILURE);
	if (ft_lstsize(parsed) != 1
		|| (ft_strcmp(cmd, "exit") != 0
		&& ft_strcmp(cmd, "cd") != 0))
		return (FAILURE);
	if (check_infiles(parsed) >= 0 && pipex->file_fd[1] >= 0)
		info->exit_code = execute_builtin_if(info, parsed, pipex);
	else
		info->exit_code = 127;
	return (SUCCESS);
}

static void handle_files(t_data *pipex, t_list *parsed, t_info *info)
{
	pipex->file_fd[1] = create_outfiles(parsed);
	if (pipex->file_fd[1] == -1)
		execute_exit(info, NULL, 1);
	pipex->file_fd[0] = check_infiles(parsed);
	if (pipex->file_fd[0] == -1)
		execute_exit(info, NULL, 1);
}
