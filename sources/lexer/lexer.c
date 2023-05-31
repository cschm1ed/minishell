/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/31 17:28:06 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**iterate_through_cmd(char **lexed);

char	**lexer(char *cmd, t_info *info)
{
	char	**lexed;
	int		amt_substrs;

	if (cmd == NULL || *cmd == 0
		|| valid_num_of_quotes(cmd) == FALSE || only_isspace(cmd) == TRUE)
		return (NULL);
	amt_substrs = count_substrs(cmd);
	lexed = ft_calloc(amt_substrs + 1, sizeof(char *));
	if (!lexed)
		return (perror("malloc"), NULL);
	lexed = split_if_isspace_or_isspecial(lexed, cmd, amt_substrs);
	if (!lexed)
		return (NULL);
	if (replace_variables(info, lexed) == FAILURE)
		return (NULL);
	lexed = iterate_through_cmd(lexed);
	if (valid_num_of_specials(lexed) == FALSE)
		return (ft_free_dbl_ptr(&lexed));
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
		if (valid_num_of_quotes(lexed[i]) == FALSE)
			return (NULL);
		trimmed = trim_quotes(ft_strdup(lexed[i]));
		if (!trimmed)
			return (free (trimmed), ft_free_dbl_ptr(&lexed));
		free (lexed[i]);
		lexed[i] = trimmed;
	}
	if (ft_strlen(lexed[0]) == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(lexed[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (lexed);
}
