/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:48:50 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/26 15:48:50 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*var_list_init(char **env);

/**
 * @brief Initializes an info struct with a list of variables from an
 * 										environment array.
 *
 * @param info A pointer to the info struct to be initialized.
 * @param env The environment array.
 *
 * @return SUCCESS if successful, FAILURE otherwise.
 */
t_info	*info_init(char **env)
{
	t_info	*info;

	info = ft_calloc(sizeof(t_info), 1);
	if (info == NULL)
		return (perror("malloc"), NULL);
	info->env_lst = var_list_init(env);
	if (info->env_lst == NULL)
		return (NULL);
	return (info);
}

/**
 * @brief Initializes a list of variables from an environment array.
 *
 * @param env The environment array.
 *
 * @return A pointer to the initialized list of variables.
 */
static t_list	*var_list_init(char **env)
{
	t_list		*ret;

	ret = NULL;
	if (var_lst_add(&ret, env) == FAILURE)
		return (ft_lstclear(&ret, delete_variable), NULL);
	return (ret);
}
