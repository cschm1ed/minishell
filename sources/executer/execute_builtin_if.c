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

#include "../../includes/minishell.h"

int	execute_builtin_if(t_info *info, t_list *parsed)
{
	char	*cmd;
	int 	ret;

	cmd = lst_get_parsed(parsed)->cmd;
	ret = 129;
	if (ft_strcmp(cmd, "echo") == 0)
		ret = execute_echo(info, lst_get_parsed(parsed));
	else if (ft_strcmp(cmd, "env") == 0)
		ret = execute_env(info);
	else if (ft_strcmp(cmd, "exit") == 0)
		ret = execute_exit(info);
	else if (ft_strcmp(cmd, "export") == 0)
		ret = execute_export(info, &(lst_get_parsed(parsed)->args[1]));
	else if (ft_strcmp(cmd, "pwd") == 0)
		ret = execute_pwd(info);
	else if (ft_strcmp(cmd, "unset") == 0)
		ret = execute_unset(info, lst_get_parsed(parsed)->args++);
	else if (ft_strcmp(cmd, "cd") == 0)
		ret = execute_cd(info, lst_get_parsed(parsed)->args[1]);
	return (ret);
}
