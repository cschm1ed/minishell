/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/07 16:47:33 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief skips until it encounters a matching quote
 * (preventing the interpreting the metacharacters within quotes)
 * @param s - string to skip special character 
 * @param i - location that is currently looked at
 * @return int - true or false
 */
int	skip_until_quote(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	while (s[++(*i)] != quote)
		if (!s[*i])
			return (FALSE);
	return (TRUE);
}

/**
 * @brief skips special characters
 * 
 * @param s - string to skip special character 
 * @param i - location that is currently looked at
 * @return int - true or false
 */
int	skip_specials(char *s, int *i)
{
	char	c;

	if (s[*i] == '\0')
		return (FALSE);
	c = s[*i];
	if (ft_isspecial(c) == TRUE)
		while (s[*i + 1] && s[*i] == c && s[*i + 1] == c)
			(*i)++;
	return (TRUE);
}
