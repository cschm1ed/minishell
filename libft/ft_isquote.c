/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:14:05 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/01 23:59:08 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief checks if c is a special character ('"' '\'')
 * @param c character to check
 * @return true or false
 */
int	ft_isquote(char c)
{
	return (c == '"' || c == '\'');
}
