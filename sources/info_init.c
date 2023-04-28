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

#include "../includes/minishell.h"

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
		return (NULL);
	info->var_lst = var_list_init(env);
	if (info->var_lst == NULL)
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
	char		**split;
	t_variable	*var;
	t_list		*ret;
	int			i;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!split)
			return (perror("malloc"), NULL);
		var = ft_calloc(sizeof(t_variable), 1);
		if (!var)
			return (perror("malloc"), NULL);
		var->name = ft_strdup(split[0]);
		var->value = ft_strdup(split[1]);
		ft_free_dbl_ptr(split);
		ft_lstadd_back(&ret, ft_lstnew((void *)var));
		i ++;
	}
	return (ret);
}
