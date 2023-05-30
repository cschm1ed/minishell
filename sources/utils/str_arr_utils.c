/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:04:29 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/29 15:37:00 by lspohle          ###   ########.fr       */
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
	while (*array && (*array)[size])
		size ++;
	new = ft_calloc(size + 2, sizeof(char *));
	if (new == NULL)
		return (perror("malloc"), NULL);
	cpy_arr(*array, new);
	if (*array != NULL)
		free (*array);
	new[size] = ft_strdup(toadd);
	if (new[size] == NULL)
		return (ft_free_dbl_ptr(&new),
			free(new), perror("malloc"), NULL);
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
	char	*dup;

	i = 0;
	new_lst = NULL;
	while (arr[i])
	{
		dup = ft_strdup(arr[i]);
		if (dup == NULL)
			return (ft_lstclear(&new_lst, free), perror("malloc"), NULL);
		new_node = ft_lstnew(dup);
		if (new_node == NULL)
			return (ft_lstclear(&new_lst, free), perror("malloc"), NULL);
		ft_lstadd_back(&new_lst, new_node);
		i ++;
	}
	return (new_lst);
}

void	bubble_sort_str_array(char **array, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			if (ft_strncmp(array[j], array[j + 1], ft_strlen(array[j])) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j ++;
		}
		i ++;
	}
}

char	**env_to_arr(t_info *info)
{
	t_list		*ptr;
	t_variable	*var;
	char		*new;
	char		**out;
	int			i;

	i = 0;
	ptr = info->env_lst;
	out = ft_calloc(sizeof(char *), ft_lstsize(info->env_lst) + 1);
	if (out == NULL)
		return (NULL);
	while (ptr)
	{
		var = lst_get_var(ptr);
		new = ft_strsjoin(var->name, "=", var->value);
		if (new == NULL)
			return (ft_free_dbl_ptr(&out), NULL);
		out[i] = new;
		ptr = ptr->next;
		i ++;
	}
	return (out);
}
