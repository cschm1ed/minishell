/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:06:49 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/07 18:46:09 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_possible_paths(char *cmd, t_info *info, int ret);
static char	*get_relative_path(char *cmd, t_info *info, char **paths, int ret);
static int	valid_directory_syntax(char *path);

/**
 * @brief get accessible path of the built-in command (executable)
 * (focusing on edge cases like '/' and "./")
 *
 * @param cmd - built-in that is currently looked at
 * @param info - info struct with all neccessary info (commands, etc.)
 * @return char* - accessible path of the built-in command
 */
char	*get_path(char *cmd, t_info *info)
{
	char	*path;
	int		dir;

	if (ft_strchr(cmd, '/') != NULL)
	{
		dir = valid_directory_syntax(cmd);
		if (access(cmd, F_OK) != 0 && ft_strncmp(cmd, "./", 2) != 0
			&& dir == FALSE)
			return (ft_printf("minishell: %s: command not found\n",
					STDERR_FILENO, cmd), g_exit_code = 127, NULL);
		if (dir == FALSE)
			return (NULL);
	}
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
			return (ft_printf("minishell: %s: permission denied\n",
					STDERR_FILENO, cmd), NULL);
		else if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
	}
	path = get_possible_paths(cmd, info, dir);
	if (path == NULL && dir == FALSE)
		return (g_exit_code = 127, NULL);
	return (path);
}

/**
 * @brief get accessible path of the built-in command (executable)
 *
 * @param cmd - built-in that is currently looked at
 * @param info - info struct with all neccessary info (commands, etc.)
 * @param ret - indicates whether it's a valid file
 * @return char* - accessible path of the built-in command
 */
static char	*get_possible_paths(char *cmd, t_info *info, int valid_syntax)
{
	char	**paths;
	char	*path_var;

	path_var = lst_find_var_val(info->env_lst, "PATH");
	if (path_var == NULL)
		return (g_exit_code = 127, ft_printf("minishell: "
				"%s: command not found\n", STDERR_FILENO, cmd), NULL);
	paths = ft_split(path_var, ':');
	if (paths == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	return (get_relative_path(cmd, info, paths, valid_syntax));
}

/**
 * @brief iterates through list of paths to find executable
 * @param cmd
 * @param info
 * @param paths
 * @param valid_syntax
 * @return NULL or executable
 */
static char	*get_relative_path(char *cmd, t_info *info, char **paths,
		int valid_syntax)
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
	if (valid_syntax == FALSE)
		ft_printf("minishell: %s: command not found\n", STDERR_FILENO, cmd);
	return (ft_free_dbl_ptr(&paths), NULL);
}

/**
 * @brief checks whether the user's input is a directory instead of a file
 *
 * @param path - prospective file to check
 * @return int - 0, 1 or 3
 */
static int	valid_directory_syntax(char *path)
{
	int	i;
	DIR	*directory;

	i = 0;
	while (path[i])
	{
		if (!(path[i] == '/' || path[i] == '.' || ft_isalnum(path[i]))
			|| (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '.'))
			return (FALSE);
		i++;
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
	}
	return (g_exit_code = 126, TRUE);
}
