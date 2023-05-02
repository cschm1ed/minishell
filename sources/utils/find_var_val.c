/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_val.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:59:16 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/01 16:59:16 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *find_var_val(t_info *info, char *name)
{
	if (lst_find_var_val(info->env_lst, name))
		return (lst_find_var_val(info->env_lst, name));
	return (lst_find_var_val(info->user_vars, name));
}
