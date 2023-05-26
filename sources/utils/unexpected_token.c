/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:04:35 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/23 16:17:23 by lspohle          ###   ########.fr       */
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
		ft_printf
			("minishell: syntax error near unexpected token `newline'\n");
		return (FAILURE);
	}
	ft_printf("minishell: syntax error near unexpected token `%s'\n", token);
	return (FAILURE);
}
