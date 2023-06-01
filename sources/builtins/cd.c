/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:32:40 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/01 13:11:57 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_isdir(char *path);
static int	update_env(t_info *info);

int	execute_cd(t_info *info, char **args, int fd_out)
{
	t_variable	*variable;
	char		*tmp;
	int			flag;

	flag = FALSE;
	variable = lst_get_var(lst_find_node(info->env_lst, "USER"));
	if (!args[1])
	{
		tmp = ft_strjoin("/Users/", variable->value);
		if (tmp == NULL)
			exit_error(info, __FILE__, __LINE__, "malloc");
		flag = TRUE;
	}
	if (flag == FALSE)
		tmp = args[1];
	if (!chdir(tmp))
		return (update_env(info));
	ft_isdir(tmp);
	ft_printf("minishell: cd: %s: %s\n", STDERR_FILENO,
		tmp, strerror(errno));
	if (flag == TRUE)
		free(tmp);
	return ((void)fd_out, 1);
}

static void	ft_isdir(char *path)
{
	DIR			*directory;

	directory = opendir(path);
	if (directory)
		closedir(directory);
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
