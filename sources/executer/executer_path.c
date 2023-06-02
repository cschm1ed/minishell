/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:06:49 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/02 10:38:17 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_possible_paths(char *cmd, t_info *info);
static char	*get_relative_path(char *cmd, t_info *info, char **paths);
static int	is_directory(char *path);

char	*get_path(char *cmd, t_info *info)
{
	char	*path;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (is_directory(cmd) == TRUE)
			return (NULL);
		if (access(cmd, F_OK) != 0) {
			ft_printf("minishell: %s: command not found\n",
					  STDERR_FILENO, cmd);
			return (g_exit_code = 127, NULL);
		}
	}
		path = get_possible_paths(cmd, info);
		if (path == NULL)
		{
			ft_printf("minishell: %s: command not found\n",
				STDERR_FILENO, cmd);
			return (g_exit_code = 127, NULL);
		}
	return (path);
}

static char	*get_possible_paths(char *cmd, t_info *info)
{
	char	**paths;
	char	*path_var;

	path_var = lst_find_var_val(info->env_lst, "PATH");
	if (path_var == NULL)
		return (g_exit_code = 127,
			ft_printf("minishell: %s: command not found\n",
				STDERR_FILENO, cmd), NULL);
	paths = ft_split(path_var, ':');
	if (paths == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	return (get_relative_path(cmd, info, paths));
}

static char	*get_relative_path(char *cmd, t_info *info, char **paths)
{
	char	*joined;
	int		i;

	i = -1;
	while (paths[++i])
	{
		joined = ft_strsjoin(paths[i], "/", cmd);
		if (joined == NULL)
		{
			ft_free_dbl_ptr(&paths);
			exit_error(info, __FILE__, __LINE__, "malloc");
		}
		if (access(joined, F_OK) != -1)
			return (ft_free_dbl_ptr(&paths), joined);
		free(joined);
	}
	return (ft_free_dbl_ptr(&paths), NULL);
}

static int	is_directory(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (!(path[i] == '/' || path[i] == '.')
			|| (path [i] == '.' && path[i + 1] == '.' && path[i + 2] == '.'))
			return (FALSE);
		i ++;
	}
	ft_printf("minishell: %s: is a directory\n", STDERR_FILENO, path);
	return (g_exit_code = 126, TRUE);
}
