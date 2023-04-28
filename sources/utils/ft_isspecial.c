/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspecial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/28 16:38:56 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief checks if c is a special character ('>' '<' '$' ';' '|' '=')
 * @param c character to check
 * @return true or false
 */
int	ft_isspecial(char c)
{
	if (c == '>' || c == '<' || c == '|'
		|| c == '=' || c == '$' || c == ';')
		return (TRUE);
	return (FALSE);
}
