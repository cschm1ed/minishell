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
/*	if ((*info)->pipex)
		free_pipex(&(*info)->pipex);
	free(*info);
*/
	*info = NULL;
}

void	free_pipex(t_data **pipex)
{
	if ((*pipex)->pipe_fd)
		close_pipes((*pipex)->pipe_fd);
	if ((*pipex)->file_fd[0] != -1)
		close((*pipex)->file_fd[0]);
	if ((*pipex)->file_fd[1] != -1)
		close((*pipex)->file_fd[1]);
	if ((*pipex)->pid)
		free((*pipex)->pid);
	if ((*pipex)->cmd_path)
		free((*pipex)->cmd_path);
	free(pipex);
	pipex = NULL;
}

void	free_cmds(t_commands *commands)
{
	if (commands->raw)
		free(commands->raw);
/*	if (commands->lexed)
		ft_free_dbl_ptr(commands->lexed);*/
	if (commands->parsed)
		ft_lstclear(&(commands->parsed), delete_parsed);
	commands->raw = NULL;
	commands->lexed = NULL;
	commands->parsed = NULL;
}
