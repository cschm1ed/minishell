/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:24:23 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 23:24:23 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int no_value(t_info *info, char *arg);
static int with_value(t_info *info, char *arg);
static void invalid_identifier(char *arg, int fd_out);

int execute_export(t_info *info, char **arg, int fd_out)
{
	int i;

	i = 1;
	if (arg == NULL || arg[1] == NULL)
		return (print_sorted_lst(info, fd_out));
	while (arg[i])
	{
		if (ft_strchr(arg[i], '=') != NULL &&
			*(ft_strchr(arg[i], '=') + 1) == 0 && arg[i + 1] != NULL)
			invalid_identifier(arg[i], fd_out);
		else if (ft_strchr(arg[i], '=') == NULL
			|| *(ft_strchr(arg[i], '=') + 1) == 0)
		{
			if (no_value(info,arg[i]) == FAILURE)
				exit_error(info, __FILE__, __LINE__, "malloc");
		}
		else if (check_if_varname_is_valid(arg[i]) == FALSE)
			invalid_identifier(ft_strchr(arg[i], '=') + 1, fd_out);
		else
		{
			if (with_value(info,arg[i]) == FAILURE)
				exit_error(info, __FILE__, __LINE__, "malloc");
		}
		i ++;
	}
	return (0);
}

static int no_value(t_info *info, char *arg)
{
	char    *name;
	char    *value;
	t_list  *node;

	name = ft_strdup(arg);
	if (!name)
		return (FAILURE);
	value = ft_strdup("");
	if (value == NULL)
		return (free(name), FAILURE);
	node = lst_newvar_node(arg, value, 0);
	if (node == NULL)
		return (free(name), free(value), FAILURE);
	ft_lstadd_back(&(info->export_lst), node);
	return (SUCCESS);
}

static int with_value(t_info *info, char *arg)
{
	char    *name;
	char    *value;
	t_list  *node;

	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (name == NULL)
		return (FAILURE);
	ft_lstrmone(&(info->export_lst), lst_find_node(info->export_lst, name), delete_variable);
	ft_lstrmone(&(info->env_lst), lst_find_node(info->env_lst, name), delete_variable);
	value = ft_strdup(ft_strchr(arg, '=') + 1);
	if (value == NULL)
		return (FAILURE);
	node = lst_newvar_node(name, value, 0);
	if (node == NULL)
		return (free(name), free(value), FAILURE);
	ft_lstadd_back(&(info->env_lst), node);
	return (SUCCESS);
}

static void invalid_identifier(char *arg, int fd_out)
{
	ft_putstr_fd("export: `", fd_out);
	ft_putstr_fd(arg, fd_out);
	ft_putstr_fd("': not a valid identifier\n", fd_out);
}
