/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/03 17:54:54 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**iterate_through_cmd(char *cmd, char **substr, int amt_substr);

/**
 * @brief allocates the accurate amount of strings to store the lexed input
 * @param cmd the user's input that was read from the line
 * @return char** - the lexed array of the user's cmd
 */
char	**lexer(char *cmd, t_info *info)
{
	char	**substr;
	int		amt_substr;

	if (*cmd == 0 || !cmd || !valid_num_of_quotes(cmd, info))
		return (NULL);
	amt_substr = count_substrs(cmd);
	substr = (char **) malloc (sizeof(char *) * (amt_substr + 1));
	if (substr == NULL)
		return (perror("malloc"), NULL);
	printf(GREEN"Count: %d\n"ESC, amt_substr);
	iterate_through_cmd(cmd, substr, amt_substr);
	if (!valid_num_of_specials(substr, info))
		return (ft_free_dbl_ptr(substr));
	return (substr);
}

/**
 * @brief splits the user's command into an array of strings
 * @param cmd the user's input that was read from the line
 * @param substr the array of strings that will be returned after lexing
 * @return char** - the lexed array of the user's cmd
 */
static char	**iterate_through_cmd(char *cmd, char **substr, int amt_substr)
{
	size_t	start;
	size_t	end;
	int		i;
	int		trim_quotes;

	start = 0;
	i = -1;
	while (++i < amt_substr)
	{
		trim_quotes = locate_substr(cmd, &start, &end);
		if (cmd[end] == 0 && i != amt_substr - 1)
			return (printf(SYNERR), ft_free_dbl_ptr(substr));
		substr[i] = ft_substr(cmd, start, end - start);
		if (!substr[i])
			return (ft_free_dbl_ptr(substr));
		start = end;
		while (trim_quotes && ft_isquote(cmd[start]))
			start++;
		printf(YELLOW"String: %s$\n"ESC, substr[i]);
	}
	substr[i] = NULL;
	return (substr);
}
