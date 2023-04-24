/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:53:46 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/01 17:37:54 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd_failed(char *cmd)
{
	perror(cmd);
	exit (1);
}

void	exit_cmd_not_found(char *cmd, t_data *pipex)
{
	write(STDERR_FILENO, "pipex: ", 7);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free(pipex->cmd_path);
	ft_free_dbl_ptr(pipex->cmd_split);
	exit(127);
}
