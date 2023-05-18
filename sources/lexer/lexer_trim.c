/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:39:31 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 11:23:56 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*update_str(char *str, size_t start, size_t end);

char	*trim_quotes(char *str)
{
	size_t	i;
	size_t	start;

	i = -1;
	start = 0;
	while (str[++i])
	{
		if (ft_isquote(str[i]))
		{
			start = i + 1;
			skip_until_quote(str, &i);
			str = update_str(str, start, i);
			i -= 2;
		}
	}
	return (str);
}

static char	*update_str(char *str, size_t start, size_t end)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_substr(str, 0, start - 1);
	tmp2 = ft_substr(str, start, (end) - start);
	tmp3 = ft_substr(str, end + 1, ft_strlen(str) - (end));
	free(str);
	str = ft_strsjoin(tmp1, tmp2, tmp3);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	return (str);
}
