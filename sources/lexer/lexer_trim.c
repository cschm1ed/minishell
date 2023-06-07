/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:39:31 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/07 16:36:26 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*update_str(char *str, size_t start, size_t end);

/**
 * @brief trims the quotes appropriately
 * 
 * @param str - string to trim 
 * @return char* - trimmed string
 */
char	*trim_quotes(char *str)
{
	int	i;
	int	start;

	start = 0;
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) == TRUE)
		{
			start = i + 1;
			skip_until_quote(str, &i);
			str = update_str(str, start, i);
			i -= 2;
		}
		i++;
	}
	return (str);
}

/**
 * @brief updates the string by joining all components without specific quotes
 * 
 * @param str - string to free and rejoin
 * @param start - marking the beginning of quotes
 * @param end  - marking the end of quotes
 * @return char* - rejoined and trimmed string
 */
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
