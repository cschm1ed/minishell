/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:54:18 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/13 17:09:41 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_builtin_if(t_info *info, t_list *parsed)
{
	char	*cmd;

	cmd = lst_get_parsed(parsed)->cmd;
	if (ft_strcmp(cmd, "echo") == 0)
		info->exit_code = execute_echo(lst_get_parsed(parsed));
	else if (ft_strcmp(cmd, "env") == 0)
		info->exit_code = execute_env(info);
	else if (ft_strcmp(cmd, "exit") == 0)
		info->exit_code = execute_exit(info, &lst_get_parsed(parsed)->args[1], 0);
	else if (ft_strcmp(cmd, "export") == 0)
		info->exit_code = execute_export(info, lst_get_parsed(parsed)->args);
	else if (ft_strcmp(cmd, "pwd") == 0)
		info->exit_code = execute_pwd(info);
	else if (ft_strcmp(cmd, "unset") == 0)
		info->exit_code = execute_unset(info, &lst_get_parsed(parsed)->args[1]);
	else if (ft_strcmp(cmd, "cd") == 0)
		info->exit_code = execute_cd(info, lst_get_parsed(parsed)->args[1]);
	else
		return (129);
	return (info->exit_code);
}
