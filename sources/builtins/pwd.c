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

#include <minishell.h>

int execute_pwd(t_info *info, int fd_out)
{
	ft_putstr_fd(info->pwd, fd_out);
	ft_putchar_fd('\n', fd_out);
	return (0);
}
