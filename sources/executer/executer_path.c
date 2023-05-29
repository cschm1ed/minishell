/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:06:49 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/29 15:26:17 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_possible_paths(char *cmd, t_info *info);
static char	*get_relative_path(char *cmd, t_info *info, char **paths);

char	*get_path(char *cmd, t_info *info)
{
	char	*path;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) == -1)
			return (g_exit_code = 127,
				ft_printf("minishell: %s: command not found\n", cmd), NULL);
		return (ft_strdup(cmd));
	}
	path = get_possible_paths(cmd, info);
	if (path == NULL)
		return (g_exit_code = 127,
			ft_printf("minishell: %s: command not found\n", cmd), NULL);
	return (path);
}

static char	*get_possible_paths(char *cmd, t_info *info)
{
	char	**paths;
	char	*path_var;

	path_var = lst_find_var_val(info->env_lst, "PATH");
	if (path_var == NULL)
		return (g_exit_code = 127,
			ft_printf("minishell: %s: command not found\n", cmd), NULL);
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
