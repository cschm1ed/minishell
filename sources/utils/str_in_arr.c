/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_in_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:29:06 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/01 17:30:42 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks if a given string is in an array of strings.
 *
 * @param arr A null-terminated array of strings.
 * @param find The string to search for in the array.
 *
 * @return TRUE if the string is in the array, or FALSE otherwise.
 */
int str_in_arr(char **arr, char *find)
{
	int	i;

	i = 0;
	while (arr[i])
		if (ft_strcmp(arr[i], find) != 0)
			return (TRUE);
	return (FALSE);
}
