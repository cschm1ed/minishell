/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:26:27 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/24 15:18:53 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_info(t_info **info)
{
	if ((*info)->env_lst)
		ft_lstclear(&((*info)->env_lst), delete_variable);
	if ((*info)->user_vars)
		ft_lstclear(&((*info)->user_vars), delete_variable);
	if ((*info)->export_lst)
		ft_lstclear(&((*info)->export_lst), delete_variable);
	if ((*info)->commands)
		free_cmds((*info)->commands, *info);
	if ((*info)->pipex)
	{
		free_pipex(&(*info)->pipex);
		free((*info)->pipex);
		(*info)->pipex = NULL;
	}
	if ((*info)->pwd)
		free((*info)->pwd);
	free(*info);
	*info = NULL;
}

void	free_pipex(t_data **pipex)
{
	int i;

	i = 0;
	if (*pipex)
	{

		if ((*pipex)->file_fd[0] != -1)
			close((*pipex)->file_fd[0]);
		if ((*pipex)->file_fd[1] != -1)
			close((*pipex)->file_fd[1]);
		if ((*pipex)->pipe_fd)
		{
			while ((*pipex)->pipe_fd[i] != NULL)
			{
				close((*pipex)->pipe_fd[i][0]);
				close((*pipex)->pipe_fd[i][1]);
				free((*pipex)->pipe_fd[i]);
				i ++;
			}
			free((*pipex)->pipe_fd);
			((*pipex)->pipe_fd = NULL);
		}
		if ((*pipex)->pid)
		{
			free((*pipex)->pid);
			(*pipex)->pid = NULL;
		}
		if ((*pipex)->cmd_path)
			free((*pipex)->cmd_path);
	}
	*pipex = NULL;
}

void free_cmds(t_commands *commands, t_info *info)
{
	int i;

	i = 0;
	if (commands->raw)
		free(commands->raw);
	if (commands->parsed)
		ft_lstclear(&(commands->parsed), delete_parsed);
	if (commands->lexed)
	{
		while (commands->lexed[i])
		{
			if (commands->lexed[i][0] && ft_isprint(commands->lexed[i][0]))
			{
				free(commands->lexed[i]);
				commands->lexed[i] = NULL;
			}
			i ++;
		}
		commands->lexed = NULL;
	}
	if (info->pipex)
		free_pipex(&info->pipex);
	commands->raw = NULL;
	commands->lexed = NULL;
	commands->parsed = NULL;
	info->pipex = NULL;
}
