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

#include "../includes/minishell.h"

static int	is_even_num_of_quotes(char *s);
static int	count_substrs(char *s);
static void	skip_specials(char *s, size_t *i);
static void	skip_until_delimiter(char *s, size_t *i, char c);
static void	locate_substr(char *s, size_t *start, size_t *end);
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
	printf(GREEN"Count: %d\n"ESC, amt_substr);
	return (iterate_through_cmd(cmd, substr, amt_substr));
}

/**
 * @brief checks if the user's input contains even number of quotation marks
 * @param cmd the user's input that was read from the line
 * @return true or false
 */
static int	is_even_num_of_quotes(char *s)
{
	int		dbl_qte;
	int		sng_qte;
	int		i;

	dbl_qte = 0;
	sng_qte = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"')
			dbl_qte++;
		else if (s[i] == '\'')
			sng_qte++;
	}
	if (dbl_qte % 2 != 0 || sng_qte % 2 != 0)
		return (printf("minishell: syntax error near unexpected token\n"), FALSE);
	return (TRUE);
}

/**
 * @brief counts substrings of the prospective lexed array of strings
 * @param s the user's input that was read from the line
 * @return int 
 */
static int	count_substrs(char *s)
{
	size_t	i;
	int		cnt;

	i = 0;
	skip_specials(s, &i);
	cnt = 1;
	while (s[++i])
	{
		if (s[i] == ' '
			|| ft_isspecial(s[i]) == TRUE || ft_isspecial(s[i - 1]) == TRUE)
		{
			skip_specials(s, &i);
			skip_until_delimiter(s, &i, s[i]);
			cnt++;
		}
	}
	return (cnt);
}

/**
 * @brief skips all specails ('>' '<' '||' ' ')
 * @param s the user's input that was read from the line
 * @param i index to continue interating through the user's input
 * @return void
 */
static void	skip_specials(char *s, size_t *i)
{
	while (s[*i] == ' '
		|| (ft_isspecial(s[*i]) == TRUE && ft_isspecial(s[*i + 1]) == TRUE))
		(*i)++;
}

/**
 * @brief skips chars until encountaring a delimter ('>' '<' '||' ' ' '"' '\'')
 * @param s the user's input that was read from the line
 * @param i index to continue interating through the user's input
 * @param c the char to determine if spaces need to be skipped (within quotes)
 * @return void
 */
static void	skip_until_delimiter(char *s, size_t *i, char c)
{
	if (c == '"' || c == '\'')
		(*i)++;
	while (s[*i] && s[*i] != c && ft_isspecial(s[*i]) == FALSE)
		(*i)++;
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

	start = 0;
	i = -1;
	while (++i < amt_substr)
	{
		locate_substr(cmd, &start, &end);
		substr[i] = ft_substr(cmd, start, end - start);
		substr[i] = ft_strtrim(substr[i], " ");
		if (!substr[i])
			return (ft_free_dbl_ptr(substr));
		printf(YELLOW"String: $%s$\n"ESC, substr[i]);
		start = end;
		if (cmd[start] == '"' || cmd[start] == '\'')
			start++;
	}
	substr[i] = NULL;
	return (substr);
}

/**
 * @brief splits the user's command into an array of strings
 * @param s the user's input that was read from the line
 * @param start start of the string that will be terminated by the delimiter
 * @param end skip until delimiter to terminate the string by using end
 * @return void
 */
static void	locate_substr(char *s, size_t *start, size_t *end)
{
	while (s[(*start)] && s[(*start)] == ' ')
		(*start)++;
	(*end) = (*start);
	while (ft_isspecial(s[(*end)]) == TRUE)
		if (ft_isspecial(s[(++(*end))]) == FALSE)
			return ;
	if (s[(*end)] == '"' || s[(*end)] == '\'')
	{
		skip_until_delimiter(s, end, s[(*end)]);
		(*start)++;
	}
	else
		skip_until_delimiter(s, end, ' ');
}
