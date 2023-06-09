/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:35:51 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/01 13:21:48 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_pwd(t_info *info, char **args, int fd_out)
{
	ft_printf("%s\n", fd_out, info->pwd);
	return ((void)args, 0);
}
