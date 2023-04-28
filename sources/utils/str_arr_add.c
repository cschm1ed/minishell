/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:04:29 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/25 13:17:20 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief str_arr_add - expands an existing str array with another string
 * @param arr - array to be expanded
 * @param toadd - string to add to the array
 * expands an existing str array with another string, frees the old array.
 * @return char** 
 */

char	**str_arr_add(char **array, char *toadd)
{
	int		size;
	int		j;
	char	**new;

	j = 0;
	size = 0;
	if (!array)
	{
		array = ft_calloc(sizeof(char *), 2);
		if (!array)
			return (perror("malloc"), NULL);
		return (array);
	}
	if (!toadd)
		return (array);
	while (array[size])
		size ++;
	new = ft_calloc(sizeof(char *), (size + 2));
	if (!new)
		return (perror("malloc"), NULL);
	ft_memmove(new, array, sizeof(char *) * size);
	new[j] = toadd;
	free(array);
	return (new);
}
