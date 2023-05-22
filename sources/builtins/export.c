/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                           :+:      :+:    :+:   */
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

int	execute_export(t_info *info, char **arg)
{
	int i;

	i = 1;
	if (arg == NULL || arg[1] == NULL)
		return (print_sorted_lst(info));
	while (arg[i])
	{
		if (ft_strchr(arg[i], '=') == NULL
			|| *(ft_strchr(arg[i], '=') + 1) == 0)
		{
			if (no_value(info,arg[i]) == FAILURE)
				return (printf("export failed"), FAILURE);
		}
		else if (check_if_varname_is_valid(arg[i]) == FALSE)
			ft_printf("export: not an identifier: %s\n", arg[i]);
		else
		{
			if (with_value(info,arg[i]) == FAILURE)
				return (printf("export failed"), FAILURE);
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
