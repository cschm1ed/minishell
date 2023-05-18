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

/**
 * @brief Converts a null-terminated array of strings into a linked list.
 *
 * @param arr A null-terminated array of strings.
 *
 * @return A pointer to the head of the linked list,
 * 										or NULL if an error occurs.
 */
t_list	*str_arr_to_lst(char **arr)
{
	int		i;
	t_list	*new_lst;
	t_list	*new_node;

	i = 0;
	new_lst = NULL;
	while (arr[i])
	{
		new_node = ft_lstnew((void *)arr[i]);
		if (!new_node)
			return (perror("malloc"), NULL);
		ft_lstadd_back(&new_lst, new_node);
		i ++;
	}
	return (new_lst);
}

/**
 * @brief Checks if a given string is in an array of strings.
 *
 * @param arr A null-terminated array of strings.
 * @param find The string to search for in the array.
 *
 * @return TRUE if the string is in the array, or FALSE otherwise.
 */
int	str_in_arr(char **arr, char *find)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], find) != 0)
			return (TRUE);
		i ++;
	}
	return (FALSE);
}
