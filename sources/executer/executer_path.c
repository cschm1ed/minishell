/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:06:49 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/02 11:31:55 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_possible_paths(char *cmd, t_info *info, int ret);
static char	*get_relative_path(char *cmd, t_info *info, char **paths, int ret);
static int	is_directory(char *path);

char	*get_path(char *cmd, t_info *info)
{
	char	*path;
	int		ret;

	ret = 0;
	if (ft_strchr(cmd, '/') != NULL)
	{
		ret = is_directory(cmd);
		if (ret == FALSE)
			return (NULL);
		if (access(cmd, F_OK) != 0 && ft_strncmp(cmd, "./", 2) != 0 && ret != 3)
			return (ft_printf("minishell: %s: command not found1\n",
					STDERR_FILENO, cmd), g_exit_code = 127, NULL);
	}
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
			return (ft_printf("minishell: %s: permission denied\n",
					STDERR_FILENO, cmd), NULL);
		else if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
	}
	path = get_possible_paths(cmd, info, ret);
	if (path == NULL && ret != 3)
		return (g_exit_code = 127, NULL);
	return (path);
}

static char	*get_possible_paths(char *cmd, t_info *info, int ret)
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
	return (get_relative_path(cmd, info, paths, ret));
}

static char	*get_relative_path(char *cmd, t_info *info, char **paths, int ret)
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
	if (ret != 3)
		ft_printf("minishell: %s: command not found\n", STDERR_FILENO, cmd);
	return (ft_free_dbl_ptr(&paths), NULL);
}

static int	is_directory(char *path)
{
	int	i;
	DIR	*directory;

	i = 0;
	while (path[i])
	{
		if (!(path[i] == '/' || path[i] == '.' || ft_isalnum(path[i]))
			|| (path [i] == '.' && path[i + 1] == '.' && path[i + 2] == '.'))
			return (FALSE);
		i ++;
	}
	directory = opendir(path);
	if (directory)
	{
		ft_printf("minishell: %s: is a directory\n", STDERR_FILENO, path);
		closedir(directory);
	}
	else
	{
		if (access(path, F_OK) == -1)
			ft_printf("minishell: %s: No such file or directory\n",
				STDERR_FILENO, path);
		return (g_exit_code = 126, 3);
	}
	return (g_exit_code = 126, TRUE);
}
