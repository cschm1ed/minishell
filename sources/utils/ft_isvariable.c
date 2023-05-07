/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvariable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:25:47 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/03 17:31:37 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief checks if c is '$' followed by a sequence of characters
 * @param c character to check if '$'
 * @param next character to check if sequence of characters 
 * @return true or false
 */
int	ft_isvariable(char before, char c, char next)
{
	return (!ft_isspace(before) && c == '$' && !ft_isspace(next));
}
