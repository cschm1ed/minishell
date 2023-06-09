/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:55:07 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/01 13:22:38 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_name(char *str);

int	execute_unset(t_info *info, char **arg, int fd_out)
{
	int	i;

	i = 1;
	if (arg == NULL || arg[0] == NULL)
		return (1);
	while (arg[i])
	{
		if (check_name(arg[i]) == FALSE)
			return (ft_printf("unset: `%s': not a valid identifier\n",
					fd_out, arg[i]), SUCCESS);
		ft_lstrmone((&info->env_lst), lst_find_node(info->env_lst, arg[i]),
			delete_variable);
		ft_lstrmone(&(info->export_lst), lst_find_node(info->export_lst,
				arg[i]), delete_variable);
		ft_lstrmone(&(info->user_vars), lst_find_node(info->user_vars, arg[i]),
			delete_variable);
		i ++;
	}
	return (SUCCESS);
}

static int	check_name(char *str)
{
	int	i;

	i = 0;
	if (*str == 0)
		return (TRUE);
	if ((ft_isalpha(str[0]) == FALSE)
		&& str[i] != '_')
		return (FALSE);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == FALSE
			&& str[i] != '_')
			return (FALSE);
		i ++;
	}
	return (TRUE);
}
