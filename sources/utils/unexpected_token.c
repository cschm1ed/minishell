/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:04:35 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/06 14:04:35 by cschmied         ###   ########.fr       */
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
	ft_printf("minishell: syntax error near unexpected token `%s'\n", token);
	return (FAILURE);
}
