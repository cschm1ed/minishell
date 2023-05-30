/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:04:35 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/30 17:02:40 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Displays the following error message: "minishell: syntax error
 * near unexpected token `<token>'\n".
 *
 * @param token - str to be displayed in error message
 * @return
 */
int	unexpected_token(char *token)
{
	g_exit_code = 258;
	if (token == NULL)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (FAILURE);
	}
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (FAILURE);
}
