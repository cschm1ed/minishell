/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:46:16 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/01 17:37:07 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# define CYAN "\e[38;5;51m"
# define GREEN "\e[38;5;47m"
# define PURPLE "\e[38;5;219m"
# define RED "\e[38;5;196m"
# define ESC "\033[0m"

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	int		pipe_fd[2];
	int		file_fd[2];
	pid_t	pid;
	char	**env_paths;
	char	**cmd_split;
	char	*cmd_path;
}				t_data;

void	exit_cmd_failed(char *cmd);
void	exit_open_failed(char *str, int fd);
void	exit_cmd_not_found(char *cmd, t_data *pipex);
void	ft_split_cmd_path(t_data *pipex, int i);
void	ft_child_process(t_data *pipex, char *cmd);
void	ft_parent_process(t_data *pipex);
char	**ft_split_cmd(char *cmd);

#endif