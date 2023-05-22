/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:39:31 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/22 18:00:03 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	terminate_string(char *s, size_t *i);

int	count_substrs(char *s)
{
	int		cnt;
	size_t	i;

	cnt = 0;
	i = -1;
	while (s[++i])
	{
		if (ft_isspace(s[i]) == FALSE)
		{
			cnt++;
			terminate_string(s, &i);
			skip_specials(s, &i);
		}
	}
	return (cnt);
}

char	**split_if_isspace_or_isspecial(char **split, char *s, int amt_substrs)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && (int) j < amt_substrs)
	{
		start = i;
		if (s[i] && ft_isspace(s[i]) == FALSE)
		{
			if (ft_isspecial(s[i]) == TRUE || terminate_string(s, &i) == FALSE)
			{
				skip_specials(s, &i);
				i++;
			}
			split[j] = ft_substr(s, start, i - start);
			if (!split[j++])
				return (ft_free_dbl_ptr(split));
			start = i;
		}
		else
			i++;
	}
	return (split);
}

static int	terminate_string(char *s, size_t *i)
{
	while (s[*i] && ft_isspace(s[*i]) == FALSE && ft_isspecial(s[*i]) == FALSE)
	{
		if (ft_isspecial(s[*i + 1]) == TRUE)
			return (FALSE);
		if (ft_isquote(s[*i]) == TRUE)
			skip_until_quote(s, i);
		(*i)++;
	}
	return (TRUE);
}
