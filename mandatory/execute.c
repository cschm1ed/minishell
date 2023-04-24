/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:53:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/01 18:27:43 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_env_path(char **envp)
{
	if (*envp == NULL)
		return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/ \
				local/munki:/opt/X11/bin:/Library/Apple/usr/bin");
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	return (*envp + 5);
}

static char	*ft_get_cmd_path(t_data *pipex, char *cmd)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	pipex->env_paths = ft_split(ft_get_env_path(pipex->envp), ':');
	if (pipex->env_paths == NULL)
		ft_free_dbl_ptr(pipex->env_paths);
	i = -1;
	while (pipex->env_paths[++i] != NULL)
	{
		tmp = ft_strjoin(pipex->env_paths[i], "/");
		free(pipex->env_paths[i]);
		pipex->env_paths[i] = tmp;
		cmd_path = ft_strjoin(pipex->env_paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			ft_free_dbl_ptr(pipex->env_paths);
			return (cmd_path);
		}
		free (cmd_path);
	}
	if ((pipex->env_paths[i] != NULL))
		ft_free_dbl_ptr(pipex->env_paths);
	return (NULL);
}

void	ft_split_cmd_path(t_data *pipex, char *cmd)
{
	pipex->cmd_split = ft_split_cmd(cmd);
	if (pipex->cmd_split == NULL)
		exit_cmd_failed("split");
	if (pipex->cmd_split[0][0] == '/')
		pipex->cmd_path = ft_strdup(pipex->cmd_split[0]);
	else
		pipex->cmd_path = ft_get_cmd_path(pipex, pipex->cmd_split[0]);
	if (pipex->cmd_path == NULL)
		exit_cmd_not_found(pipex->cmd_split[0], pipex);
}

void	ft_child_process(t_data *pipex, char *cmd)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (execve(pipex->cmd_path, pipex->cmd_split, pipex->envp) <= -1)
		exit_cmd_not_found(pipex->cmd_split[0], pipex);
}

void	ft_parent_process(t_data *pipex)
{
	waitpid(pipex->pid, NULL, WNOHANG);
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
}
