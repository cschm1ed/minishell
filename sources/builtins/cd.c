/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:32:40 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/01 12:48:38 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	update_env(t_info *info);

int execute_cd(t_info *info, char **args, int fd_out)
{
	t_variable	*variable;
	DIR			*directory;
	char		*tmp;
	
	variable = lst_get_var(lst_find_node(info->env_lst, "USER"));
	if (!args[1])
	{
		tmp = ft_strjoin("/Users/", variable->value);
		if (tmp == NULL)
			exit_error(info, __FILE__, __LINE__, "malloc");
		if (str_arr_add(&args, tmp) == NULL)
			exit_error(info, __FILE__, __LINE__, "malloc");

	}
	if (!chdir(args[1]))
		return (update_env(info));
	directory = opendir(args[1]);
	if (directory)
		closedir(directory);
	(void)fd_out;
	return (ft_printf("minishell: cd: %s: %s\n", STDERR_FILENO,
	                  args[1], strerror(errno)), 1);
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
