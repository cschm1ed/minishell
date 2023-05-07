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

/**
 * returns the value of the variable searched for by looking through
 * the env_lst and user_vars list.
 *
 * @param info - general info struct
 * @param name - name of the variable whose value is sought
 * @return
 */
char	*find_var_val(t_info *info, char *name)
{
	if (lst_find_var_val(info->env_lst, name))
		return (lst_find_var_val(info->env_lst, name));
	return (lst_find_var_val(info->user_vars, name));
}
