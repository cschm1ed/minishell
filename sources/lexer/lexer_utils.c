/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/05 10:39:59 by lspohle          ###   ########.fr       */
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

int	skip_specials(char *s, size_t *i)
{
	while ((s[*i + 1] && ft_isspecial(s[*i]) && ft_isspecial(s[*i + 1])))
		(*i)++;
	return (TRUE);
}
