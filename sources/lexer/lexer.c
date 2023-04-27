/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/26 20:31:02 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**iterate_through_cmd(char *cmd, char **substr, int amt_substr);

/**
 * @brief allocates the accurate amount of strings to store the lexed input
 * @param cmd the user's input that was read from the line
 * @return char** - the lexed array of strings
 */
char	**lexer(char *cmd)
{
	char	**substr;
	int		amt_substr;

	if (*cmd == 0 || !cmd || is_even_num_of_quotes(cmd) == FALSE)
		return (NULL);
	amt_substr = count_substrs(cmd);
	substr = (char **) malloc (sizeof(char *) * (amt_substr + 1));
	if (substr == NULL)
		return (perror("malloc"), NULL);
	//printf(GREEN"Count: %d\n"ESC, amt_substr);
	iterate_through_cmd(cmd, substr, amt_substr);
	if (are_valid_quotes(substr) == FALSE)
		return (ft_free_dbl_ptr(substr));
	return (substr);
}

/**
 * @brief splits the user's command into an array of strings
 * @param cmd the user's input that was read from the line
 * @param substr the array of strings that will be returned after lexing
 * @return char** - the lexed array of strings
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
		substr[i] = ft_strtrim(substr[i], " ");
		if (!substr[i])
			return (ft_free_dbl_ptr(substr));
		start = end;
		while ((trim_quotes == TRUE && cmd[start] == '"')
			|| (trim_quotes == TRUE && cmd[start] == '\''))
			start++;
		//printf(YELLOW"String: %s\n"ESC, substr[i]);
	}
	substr[i] = NULL;
	return (substr);
}
