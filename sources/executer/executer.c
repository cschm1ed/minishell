/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:42:15 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/03 19:15:28 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executer(t_info *info, t_commands commands)
{
	if (ft_strncmp(commands.parsed->cmd, "pwd", 4) == 0)
		execute_pwd(info);
	else if (ft_strncmp(commands.parsed->cmd, "echo", 5) == 0)
		execute_echo(commands.parsed);
	return (TRUE);
}
