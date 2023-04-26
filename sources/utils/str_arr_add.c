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

char	**str_arr_add(char ***array, char *toadd)
{
	int		size;
	int		j;
	char    **new;
	char    **arr;

	j = 0;
	size = 0;
	arr = *array;
	if (!toadd)
		return (*array);
	while (arr[size])
		size ++;
	new = ft_calloc(sizeof(char*), (size + 2));
	if (!new)
		return (perror("malloc"), NULL);
	while (arr[j])
	{
		new[j] = arr[j];
		j ++;
	}
	new[j] = toadd;
	free(*array);
	return (new);
}
