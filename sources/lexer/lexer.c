/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/12 16:30:32 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**iterate_through_cmd(char **lexed);

void	print_lexed(char **array)
{
	int i;

	i = -1;
	while (array[++i])
		ft_printf(CYAN"%s\n"ESC, array[i]);
}

char	**lexer(char *cmd, t_info *info)
{
	char	**lexed;
	int		amt_substrs;

	if (cmd == NULL || *cmd == 0 || !valid_num_of_quotes(cmd, info))
		return (NULL);
	amt_substrs = count_substrs(cmd);
	// printf(GREEN"Count: %d\n"ESC, amt_substrs);
	lexed = malloc ((amt_substrs + 1) * sizeof(char *));
	if (!lexed)
		return (perror("malloc"), NULL);
	lexed = split_if_isspace(lexed, cmd, amt_substrs);
	if (!lexed)
		return (NULL);
	if (!replace_variables(info, lexed))
	 	return (NULL);
	lexed = iterate_through_cmd(lexed);
	if (!valid_num_of_specials(lexed, info))
		return (ft_free_dbl_ptr(lexed));
	return (lexed);
}

/**
 * @brief splits the user's command into an array of strings
 * @param cmd the user's input that was read from the line
 * @param substr the array of strings that will be returned after lexing
 * @return char** - the lexed array of the user's cmd
 */
static char	**iterate_through_cmd(char **lexed)
{
	char	*trimmed;
	int		i;

	i = -1;
	while (lexed[++i])
	{
		trimmed = trim_quotes(ft_strdup(lexed[i]));
		if (!trimmed)
			return (free (trimmed), ft_free_dbl_ptr(lexed));
		free (lexed[i]);
		lexed[i] = trimmed;
	}
	return (lexed);
}
