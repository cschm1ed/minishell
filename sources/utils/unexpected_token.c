/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:04:35 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/01 16:00:12 by cschmied         ###   ########.fr       */
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
		ft_printf("minishell: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (FAILURE);
	}
	ft_printf("minishell: syntax error near unexpected token `%s'\n",
		STDERR_FILENO, token);
	return (FAILURE);
}
