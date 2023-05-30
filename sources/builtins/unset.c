/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:55:07 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 22:55:07 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	invalid_identifier(char *arg, int fd_out);

int execute_unset(t_info *info, char **arg, int fd_out)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (check_if_varname_is_valid(arg[i]) == FALSE)
			return (invalid_identifier(arg[i], fd_out), 1);
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

static void	invalid_identifier(char *arg, int fd_out)
{
	ft_putstr_fd("unset: `", fd_out);
	ft_putstr_fd(arg, fd_out);
	ft_putstr_fd("': not a valid identifier\n", fd_out);
}