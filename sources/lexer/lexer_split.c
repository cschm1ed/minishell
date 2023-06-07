/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:39:31 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/07 16:42:05 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	terminate_string(char *s, int *i);

/**
 * @brief counts the prospective substrings of the splitted cmd
 * 
 * @param s - the user's input which needs to be splitted into an array
 * @return int - amount of substrings
 */
int	count_substrs(char *s)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (ft_isspace(s[i]) == FALSE)
		{
			cnt++;
			terminate_string(s, &i);
			skip_specials(s, &i);
		}
		if (s[i])
			i ++;
	}
	return (cnt);
}

/**
 * @brief splits the user's input into a two dimensional array
 * (depending on isspace and isspecial)
 * 
 * @param split - splitted array to return
 * @param s - the user's input which needs to be splitted 
 * @param substrs - the calculated amount of substrings needed 
 * @return char** - splitted array
 */
char	**split_cmd(char **split, char *s, int substrs)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && (int) j < substrs)
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
				return (ft_free_dbl_ptr(&split));
			start = i;
		}
		else
			i++;
	}
	return (split);
}

/**
 * @brief terminates the string appropriately
 * (depending on isspace or isspecial)
 * (skipping metacharacters within quotes)
 * 
 * @param s - string to terminate
 * @param i - location that is currently looked at
 * @return int 
 */
static int	terminate_string(char *s, int *i)
{
	while (s[*i] && ft_isspace(s[*i]) == FALSE && ft_isspecial(s[*i]) == FALSE)
	{
		if (ft_isquote(s[*i]) == TRUE)
			skip_until_quote(s, i);
		if (ft_isspecial(s[*i + 1]) == TRUE)
			return (FALSE);
		if (s[*i])
			(*i)++;
	}
	return (TRUE);
}
