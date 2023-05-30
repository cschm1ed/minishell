/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/30 15:15:30 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_until_quote(const char *s, int *i)
{
	char	quote;

	quote = s[*i];
	while (s[++(*i)] != quote)
		if (!s[*i])
			return (FALSE);
	return (TRUE);
}

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
