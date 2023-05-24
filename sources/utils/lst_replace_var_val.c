/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_replace_var_val.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:03:16 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/24 15:22:21 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	lst_replace_var_val(t_list *list, char *name, char *new)
{
	char	*replacement;

	replacement = ft_strdup(new);
	if (replacement == NULL)
		return (perror("malloc"), FAILURE);
	if (lst_find_node(list, name) != NULL)
		lst_get_var(lst_find_node(list, name))->value = replacement;
	else
		free(replacement);
	return (SUCCESS);
}
