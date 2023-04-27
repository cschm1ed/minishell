/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/26 20:31:02 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief checks if the user's input contains even number of quotation marks
 * @param cmd the user's input that was read from the line
 * @return true or false
 */
int	is_even_num_of_quotes(char *s)
{
	int		dbl_qte;
	int		sng_qte;
	int		i;

	dbl_qte = 0;
	sng_qte = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"')
			dbl_qte++;
		else if (s[i] == '\'')
			sng_qte++;
	}
	if (dbl_qte % 2 != 0 || sng_qte % 2 != 0)
		return (printf(SYNERR), FALSE);
	return (TRUE);
}

/**
 * @brief checks if the user's input contains invalid quotes
 * @param substr the user's input lexed into an array
 * @return true or false
 */
int	are_valid_quotes(char **substr)
{
	int	str;
	int	i;

	str = -1;
	while (substr[++str])
	{
		i = -1;
		while (substr[str][++i])
		{
			if (substr[str][i] == '"' || substr[str][i] == '\'')
				return (printf(SYNERR), FALSE);
		}
	}
	return (TRUE);
}
