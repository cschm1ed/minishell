/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:32:40 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/30 16:22:48 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	update_env(t_info *info);

int	execute_cd(t_info *info, char *dir)
{
	t_variable	*variable;
	DIR			*directory;

	variable = (t_variable *)lst_find_node(info->env_lst, "USER")->content;
	if (!dir)
	{
		dir = ft_strjoin("/Users/", variable->value);
		if (!dir)
			exit_error(info, __FILE__, __LINE__, "malloc");
	}
	if (!chdir(dir))
		return (update_env(info));
	directory = opendir(dir);
	if (directory)
		closedir(directory);
	return (ft_printf("minishell: cd: %s: %s\n", dir, strerror(errno)), 1);
}

static int	update_env(t_info *info)
{
	char	*updated_pwd;

	updated_pwd = getcwd(NULL, 0);
	if (!updated_pwd)
		return (perror("minishell: cd"), 1);
	free (info->pwd);
	info->pwd = updated_pwd;
	if (lst_replace_var_val(info->env_lst, "PWD", updated_pwd) == FAILURE)
		return (1);
	return (0);
}
