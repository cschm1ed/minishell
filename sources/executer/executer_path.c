/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:06:49 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/24 17:06:49 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_relative_path(char *cmd, t_info *info);

char *get_path(char *cmd, t_info *info)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) == -1)
			return (g_exit_code = 127, ft_printf("minishell: %s: command not found\n", cmd), NULL);
		return (ft_strdup(cmd));
	}
	get_relative_path(cmd, info);
	return (g_exit_code = 127, ft_printf("minishell: %s: command not found\n", cmd), NULL);
}

static char	*get_relative_path(char *cmd, t_info *info)
{
	char    *joined;
	char    **paths;
	char    *path_var;
	int	i;

	path_var = lst_find_var_val(info->env_lst, "PATH");
	if (path_var == NULL)
		return (g_exit_code = 127, ft_printf("minishell: %s: command not found\n", cmd), NULL);
	paths = ft_split(path_var, ':');
	if (paths == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	i = 0;
	while (paths[i])
	{
		joined = ft_strsjoin(paths[i], "/", cmd);
		if (joined == NULL)
		{
			ft_free_dbl_ptr(paths);
			exit_error(info, __FILE__, __LINE__, "malloc");
		}
		if (access(joined, F_OK) != -1)
			return (ft_free_dbl_ptr(paths), joined);
		i ++;
	}
	return (NULL);
}
