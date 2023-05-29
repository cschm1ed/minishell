/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:39:31 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/29 13:57:57 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*update_str(char *str, size_t start, size_t end);

char	*trim_quotes(char *str)
{
	int	i;
	int	start;

	i = -1;
	start = 0;
	if (str == NULL)
		return (NULL);
	while (str[++i])
	{
		if (ft_isquote(str[i]) == TRUE)
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

	if (str + start == 0)
		return (NULL);
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
