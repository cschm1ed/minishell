/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:32:40 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/30 15:24:01 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_edge_cases(const char *s1, const char *s2, const char *s3)
{
	if (!s1 && !s2 && !s3)
		return (NULL);
	else if (!s1 && !s2)
		return (ft_strdup(s3));
	else if (!s1 && !s3)
		return (ft_strdup(s2));
	else if (!s2 && !s3)
		return (ft_strdup(s1));
	else if (!s1)
		return (ft_strjoin(s2, s3));
	else if (!s2)
		return (ft_strjoin(s1, s3));
	else
		return (ft_strjoin(s1, s2));
}

char	*ft_strsjoin(const char *s1, const char *s2, const char *s3)
{
	char	*result;

	if (!s1 || !s2 || !s3)
		return (join_edge_cases(s1, s2, s3));
	result = ft_calloc(ft_strlen(s1) + ft_strlen(s2)
			+ ft_strlen(s3) + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_memmove(result, s1, ft_strlen(s1));
	ft_memmove(ft_strchr(result, 0), s2, ft_strlen(s2));
	ft_memmove(ft_strchr(result, 0), s3, ft_strlen(s3));
	return (result);
}
