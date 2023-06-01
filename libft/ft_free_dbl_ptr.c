/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dbl_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:36:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/01 13:17:08 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_dbl_ptr(char ***array)
{
	int		i;

	i = 0;
	if (*array)
	{
		while ((*array)[i])
		{
			free((*array)[i]);
			i ++;
		}
		free(*array);
	}
	*array = NULL;
	return (NULL);
}
