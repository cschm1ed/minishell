/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:24:23 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 23:24:23 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_sorted_lst(t_info *info);

int	export(t_info *info, char **arg)
{
	int i;

	i = 0;
	if (arg == NULL)
	{
		print_sorted_lst(info);
		return (SUCCESS);
	}
	return (var_lst_add(info->env_lst, arg)
}

static void	print_sorted_lst(t_info *info)
{
	t_info	*cpy;


}
