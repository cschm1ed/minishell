/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts_find_var_val.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:23:02 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/24 15:23:07 by lspohle          ###   ########.fr       */
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
char	*lsts_find_var_val(t_info *info, char *name)
{
	if (lst_find_var_val(info->env_lst, name))
		return (lst_find_var_val(info->env_lst, name));
	if (lst_find_var_val(info->export_lst, name))
		return (lst_find_var_val(info->export_lst, name));
	else
		return (lst_find_var_val(info->user_vars, name));
}
