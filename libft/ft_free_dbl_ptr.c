/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dbl_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:36:03 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/01 17:33:54 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_dbl_ptr(char **array)
{
	int		i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (NULL);
}
