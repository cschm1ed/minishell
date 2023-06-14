/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:26:27 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/14 13:03:07 by lspohle          ###   ########.fr       */
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
	if ((*info)->pwd)
		free((*info)->pwd);
	if ((*info)->builtins)
		free((*info)->builtins);
	if ((*info)->home_path)
		free((*info)->home_path);
	free(*info);
	*info = NULL;
}

void	free_pipex(t_data **pipex)
{
	if (*pipex)
	{
		if ((*pipex)->file_fd[0] > 1)
			close((*pipex)->file_fd[0]);
		if ((*pipex)->file_fd[1] > 1)
			close((*pipex)->file_fd[1]);
		if ((*pipex)->pipe_fd)
		{
			close_pipes(pipex);
			free((*pipex)->pipe_fd);
		}
		if ((*pipex)->pid)
			free((*pipex)->pid);
		if ((*pipex)->cmd_path)
			free((*pipex)->cmd_path);
		free(*pipex);
	}
	*pipex = NULL;
}

void	free_cmds(t_commands *commands, t_info *info)
{
	if (commands->raw)
		free(commands->raw);
	if (commands->parsed)
		ft_lstclear(&(commands->parsed), delete_parsed);
	if (info && info->token_lst)
		ft_lstclear(&info->token_lst, free);
	if (commands->lexed)
		ft_free_dbl_ptr(&commands->lexed);
	if (info->pipex)
		free_pipex(&info->pipex);
	if (info->preserve_literal)
		free(info->preserve_literal);
	info->token_lst = NULL;
	info->preserve_literal = NULL;
	commands->raw = NULL;
	commands->lexed = NULL;
	commands->parsed = NULL;
	info->pipex = NULL;
}

void	close_pipes(t_data **pipex)
{
	int	i;

	i = 0;
	while ((*pipex)->pipe_fd[i] != NULL)
	{
		if ((*pipex)->pipe_fd[i][0] > 2)
			close((*pipex)->pipe_fd[i][0]);
		if ((*pipex)->pipe_fd[i][1] > 2)
			close((*pipex)->pipe_fd[i][1]);
		(*pipex)->pipe_fd[i][0] = -1;
		(*pipex)->pipe_fd[i][1] = -1;
		free((*pipex)->pipe_fd[i]);
		i ++;
	}
}

void	exit_error(t_info *info, char *file, int line, char *msg)
{
	if (file)
		ft_printf("%s: ", STDERR_FILENO, file);
	if (line)
		ft_printf("c (%d): ", STDERR_FILENO, line);
	if (msg)
		perror(msg);
	execute_exit(info, NULL, 1);
}
