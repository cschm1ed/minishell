/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:35:51 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/03 19:26:05 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_pwd(t_info *info)
{
	//printf("%s\n", info->env_lst->pwd);
	printf("%s\n", lst_find_var_val(info->env_lst, "PWD"));
	return (SUCCESS);
}
