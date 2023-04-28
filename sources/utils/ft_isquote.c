/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:14:05 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/28 16:49:58 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief checks if c is a special character ('"' '\'')
 * @param c character to check
 * @return true or false
 */
int	ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (TRUE);
	return (FALSE);
}
