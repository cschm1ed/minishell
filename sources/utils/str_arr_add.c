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

static void	cpy_arr(char **src, char **dst);

/**
 * @brief str_arr_add - expands an existing str array with another string
 * @param arr - array to be expanded
 * @param toadd - string to add to the array
 * expands an existing str array with another string, frees the old array.
 * @return char** 
 */
char	**str_arr_add(char ***array, char *toadd)
{
	char	**new;
	int		size;

	size = 0;
	if (toadd == NULL)
		return (*array);
	if (*array == NULL)
		size = 0;
	else
	{
		while ((*array)[size])
			size ++;
	}
	new = ft_calloc(size + 2, sizeof(char *));
	if (new == NULL)
		return (perror("malloc"), NULL);
	cpy_arr(*array, new);
	new[size] = toadd;
	if (*array != NULL)
		free (*array);
	*array = new;
	return (new);
}

static void	cpy_arr(char **src, char **dst)
{
	int	i;

	i = 0;
	if (src == NULL)
		return ;
	while (src[i])
	{
		dst[i] = src[i];
		i ++;
	}
}
