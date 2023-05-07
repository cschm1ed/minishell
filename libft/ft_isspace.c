/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:03:35 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/28 16:49:28 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief checks if c is a special character (' ' '\t' '\r' '\v' '\f' '\n')
 * @param c character to check
 * @return true or false
 */
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\n');
}
