/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/22 13:11:23 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int skip_until_quote(const char *s, size_t *i)
{
	char	quote;

	quote = s[*i];
	while (s[++(*i)] != quote)
		if (!s[*i])
			return (FALSE);
	return (TRUE);
}

// int	skip_specials(char *s, size_t *i)
// {
// 	while ((s[*i + 1] && ft_isspecial(s[*i]) && ft_isspecial(s[*i + 1])))
// 		(*i)++;
// 	return (TRUE);
// }

int	skip_specials(char *s, size_t *i)
{
	char c;

	c = s[*i];
	if (ft_isspecial(c) == TRUE)
		while (s[*i + 1] && s[*i] == c && s[*i + 1] == c)
			(*i)++;
	return (TRUE);
}
