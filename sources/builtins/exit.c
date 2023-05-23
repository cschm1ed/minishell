/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:47:16 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/23 15:11:47 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int execute_exit(t_info *info, char **arg, int exit_code)
{
    // free
	if (info)
		free_info(&info);
	if (exit_code != 0)
		exit(exit_code);
	if (arg && *arg)
    	exit(ft_atoi(*arg));
	exit(0);
	return (SUCCESS);
}
