/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isredirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:31:19 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/28 16:40:53 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief checks if c is a special character ('>' '<')
 * @param c character to check
 * @return true or false
 */
int	ft_isredirect(char c)
{
	return (c == '>' || c == '<');
}
