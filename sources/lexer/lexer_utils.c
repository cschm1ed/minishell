/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/03 17:33:46 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_specials(char *cmd, size_t *i);
static int	skip_until_delimiter(char *cmd, size_t *i, char c);
static void	skip_quotes(char *cmd, size_t *start, size_t *end);

/**
 * @brief counts substrings of the prospective lexed array of strings
 * @param cmd the user's input that was read from the line
 * @return int 
 */
int	count_substrs(char *cmd)
{
	size_t	i;
	int		cnt;

	i = 0;
	skip_specials(cmd, &i);
	cnt = 1;
	while (cmd[++i])
	{
		if (ft_isspace(cmd[i]) || ft_isvariable(cmd[i], cmd[i + 1])
			|| ft_isspecial(cmd[i]) || ft_isspecial(cmd[i - 1]))
		{
			skip_specials(cmd, &i);
			if (skip_until_delimiter(cmd, &i, cmd[i]))
				cnt++;
		}
	}
	return (cnt);
}

/**
 * @brief splits the user's command into an array of strings
 * @param cmd the user's input that was read from the line
 * @param start start of the string that will be terminated by the delimiter
 * @param end skip until delimiter to terminate the string by using end
 * @return void
 */
int	locate_substr(char *cmd, size_t *start, size_t *end)
{
	while (cmd[(*start)] && ft_isspace(cmd[(*start)]))
		(*start)++;
	(*end) = (*start);
	while (cmd[(*end)] && ft_isspecial(cmd[(*end)]))
		if (!ft_isspecial(cmd[(++(*end))]))
			return (FALSE);
	if (ft_isvariable(cmd[*end], cmd[*end]))
		(*end)++;
	if (ft_isquote(cmd[(*end)]))
	{
		skip_quotes(cmd, start, end);
		skip_until_delimiter(cmd, end, cmd[(*end)]);
		(*start)++;
		return (TRUE);
	}
	else
		skip_until_delimiter(cmd, end, ' ');
	return (FALSE);
}

/**
 * @brief skips all specails ('>' '<' '||' ' ')
 * @param cmd the user's input that was read from the line
 * @param i index to continue interating through the user's input
 * @return void
 */
static void	skip_specials(char *cmd, size_t *i)
{
	if (ft_isquote(cmd[*i]))
		(*i)++;
	while ((cmd[*i + 1] != 0 && ft_isspace(cmd[*i]))
		|| (cmd[*i + 1] != 0 && ft_isspecial(cmd[*i])
			&& ft_isspecial(cmd[*i + 1])))
		(*i)++;
}

/**
 * @brief skips chars until encountaring a delimter ('>' '<' '||' ' ' '"' '\'')
 * @param s the user's input that was read from the line
 * @param i index to continue interating through the user's input
 * @param c the char to determine if spaces need to be skipped (within quotes)
 * @return void
 */
static int	skip_until_delimiter(char *cmd, size_t *i, char c)
{
	if (!cmd[(*i) + 1])
		return (FALSE);
	if (ft_isquote(c))
		while (ft_isquote(cmd[*i]))
			(*i)++;
	while (cmd[*i] && cmd[*i] != c && !ft_isspecial(cmd[*i])
		&& !ft_isvariable(cmd[*i], cmd[*i + 1]))
		(*i)++;
	return (TRUE);
}

/**
 * @brief skips all quotes ('"' '\'')
 * @param s the user's input that was read from the line
 * @param start start of the string that will be terminated by the delimiter
 * @param end skip until delimiter to terminate the string by using end
 * @return void
 */
static void	skip_quotes(char *cmd, size_t *start, size_t *end)
{
	while ((cmd[*end] == '"' && cmd[*end + 1] == '"')
		|| (cmd[*end] == '\'' && cmd[*end + 1] == '\''))
	{
		(*end)++;
		(*start)++;
	}
}
