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

static char	**iterate_through_cmd(char *cmd, char **substr);
static void	search_for_char(char *s, size_t *i, char c);
static int	check_redirections(char *s, size_t *i);
static int	check_redirections_at_beginning(char *s, size_t *i);
static int	cnt_substr(char *s);
static int	locate_substr(char *s, size_t *start, size_t *end);
static int	is_syntax_valid(char *cmd);


/**
 * @brief allocates the accurate amount of strings to store the lexed input
 * @param cmd - the user's input that was read from the line
 * @return char** - the lexed array of strings
 */
char	**lexer(char *cmd)
{
	char	**substr;

	if (*cmd == 0 || !cmd || is_syntax_valid(cmd) == FALSE)
		return (NULL);
	substr = (char **) malloc (sizeof(char *) * (cnt_substr(cmd) + 1));
	if (substr == NULL)
		return (perror("malloc"), NULL);
	//printf(GREEN"Count: %d\n"ESC, cnt_substr(cmd));
	return (iterate_through_cmd(cmd, substr));
}

/**
 * @brief splits the user's command into an array of strings
 * @param cmd - the user's input that was read from the line
 * @param substr - the array of strings that will be returned after lexing
 * @return char** - the lexed array of strings
 */
static char	**iterate_through_cmd(char *cmd, char **substr)
{
	size_t	start;
	size_t	end;
	int		i;

	start = 0;
	i = -1;
	while (++i < cnt_substr(cmd))
	{
		locate_substr(cmd, &start, &end);
		substr[i] = ft_substr(cmd, start, end - start);
		if (!substr[i])
			return (ft_free_dbl_ptr(substr));
		//printf(YELLOW"String: %s$\n"ESC, substr[i]);
		start = end;
		if (cmd[start] == '"' || cmd[start] == '\'')
			start++;
	}
	substr[i] = NULL;
	return (substr);
}

static void	search_for_char(char *s, size_t *i, char c)
{
	if (c == '"' || c == '\'')
		(*i)++;
	while (s[*i] != c && s[*i] && s[*i] != '>' && s[*i] != '<')
		(*i)++;
}

static int check_redirections(char *s, size_t *i)
{
	if (s[*i] == '>' || s[*i] == '<')
	{
		while ((s[*i] == '>' && s[*i + 1] == '>') || (s[*i] == '>' && s[*i + 1] == '<')
			|| (s[*i] == '<' && s[*i + 1] == '<') || (s[*i] == '<' && s[*i + 1] == '>'))
			(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief checks if a redirection is at the beginning of the user's input
 * @param s the user's input that was read from the line
 * @param i index to continue interating through the user's input
 * @return true or false
 */
static int check_redirections_at_beginning(char *s, size_t *i)
{
	if (s[*i] == '>' || s[*i] == '<')
		return (TRUE);
	while (s[*i] == ' ')
	{
		if (s[*i + 1] == '>' || s[*i + 1] == '<')
			return (TRUE);
		(*i)++;
	}
	return (FALSE);
}

/**
 * @brief counts substrings of the prospective lexed array of strings
 * @param s the user's input that was read from the line
 * @return int 
 */
static int	cnt_substr(char *s)
{
	size_t	i;
	int		cnt;

	i = 0;
	cnt = 1;
	if (check_redirections_at_beginning(s, &i) == TRUE)
		cnt = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '>' || s[i] == '<'
			|| s[i - 1] == '>' || s[i - 1] == '<')
		{
			while (s[i] == ' ')
 				i++;
			if (check_redirections(s, &i) == FALSE)
				search_for_char(s, &i, s[i]);
			cnt++;
		}
		i++;
	}
	return (cnt);
}

static int	locate_substr(char *s, size_t *start, size_t *end)
{
	char c;

	while (s[(*start)] == ' ' && s[(*start)])
		(*start)++;
	(*end) = (*start);
	while (s[(*end)] == '>' || s[(*end)] == '<')
	{
		*end += 1;
		if ((s[(*end)] != '>' && s[(*end)] != '<'))
			return (SUCCESS);
	}
	if (s[(*end)] == '"' || s[(*end)] == '\'')
	{
		c = s[(*end)];
		(*end)++;
		while (s[(*end)] == ' ')
		{
			(*start)++;
			(*end)++;
		}
		search_for_char(s, end, c);
		(*start)++;
	}
	else
		search_for_char(s, end, ' ');
	return (SUCCESS);
}

static int	is_syntax_valid(char *cmd)
{
	int		dbl_qte;
	int		sng_qte;
	int		i;

	dbl_qte = 0;
	sng_qte = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"')
			dbl_qte++;
		else if (cmd[i] == '\'')
			sng_qte++;
	}
	if (dbl_qte % 2 != 0 || sng_qte % 2 != 0)
		return (printf("minishell: syntax error near unexpected token\n"), FAILURE);
	return (SUCCESS);
}