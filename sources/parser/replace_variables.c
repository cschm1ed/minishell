/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 23:09:06 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/01 23:09:06 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	replace(t_info *info, t_list *node, char *name);

void	replace_variables(t_info *info, t_list *token_lst)
{
	char	*str;

	if (!token_lst)
		return ;
	while (token_lst)
	{
		str = (char *)token_lst->content;
		if (ft_strchr(str, '$'))
			replace(info, token_lst, ft_strchr(str, '$') + 1);
		token_lst = token_lst->next;
	}
}

static void	replace(t_info *info, t_list *node, char *name)
{
	char	*value;

	value = lst_find_var_val(info->env_lst, name);
	if (value)
	{
		node->content = (void *) lst_find_var_val(info->env_lst, name);
		if (!node->content)
			exit(1);
		return ;
	}
	node->content = (void *)lst_find_var_val(info->user_vars, name);
}
