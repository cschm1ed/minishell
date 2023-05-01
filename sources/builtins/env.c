/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:03:58 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 19:03:58 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_var(void *content);

void	builtin_env(t_info *info)
{
	ft_lstiter(info->env_lst, print_var);
	printf("_=/Users/cschmied/Documents/minishell/sources/builtins/env.c\n");
}

static void	print_var(void *content)
{
	t_variable *variable;

	variable = (t_variable*)content;
	printf("%s=%s\n", variable->name, variable->value);
}