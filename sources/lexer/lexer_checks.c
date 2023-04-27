/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/27 18:48:16 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief checks if the user's input contains even number of quotation marks
 * @param cmd the user's input that was read from the line
 * @return true or false
 */
int	even_num_of_quotes(char *s)
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
int	valid_quotes(char **lexed)
{
	int	str;
	int	i;

	str = -1;
	while (lexed[++str])
	{
		i = -1;
		while (lexed[str][++i])
			if (lexed[str][i] == '"' || lexed[str][i] == '\'')
				return (printf(SYNERR), FALSE);
	}
	return (TRUE);
}

static int count_specials(char *s, int *i, char c, char next)
{
	int cnt;

	cnt = 0;
	if (next == c)
		return (3);
	while (s[(*i)] && s[(*i)++] == c)
		cnt++;
	return (cnt);
}

int	valid_num_of_specials(char **lexed)
{
	int	s;
	int	i;

	s = -1;
	while (lexed[++s])
	{
		i = -1;
		while (lexed[s][++i])
		{
			if (lexed[s][i] == '>' || lexed[s][i] == '<' || lexed[s][i] == '|')
			{
				if (count_specials(lexed[s], &i, lexed[s][i], lexed[s + 1][i]) > 2)
					return (printf(PARERR), FALSE);
			}
		}
	}
	return (TRUE);
}
