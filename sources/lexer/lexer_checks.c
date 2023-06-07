/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/07 16:29:25 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_specials(char *lxd, char c);
static int	print_invalid_num_of_specials(char c, int cnt);

/**
 * @brief checks whether cmd contains only isspace
 * 
 * @param cmd - the user's input
 * @return int - true or false
 */
int	ft_isempty(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (ft_isspace(cmd[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief checks whether the amount of quotes is valid
 * 
 * @param cmd - the user's input
 * @return int - true or false
 */
int	valid_num_of_quotes(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (ft_isquote(cmd[i]) == TRUE)
		{
			if (skip_until_quote(cmd, &i) == FALSE)
				return (ft_putstr_fd(SYNERR, STDERR_FILENO),
					g_exit_code = 258, FALSE);
		}
	}
	return (TRUE);
}

/**
 * @brief checks whether the amount of specials is valid
 * 
 * @param lxd - splitted and trimmed array of the user's input
 * @return int - true or false
 */
int	valid_num_of_specials(char **lxd)
{
	int	s;
	int	i;

	s = 0;
	if (lxd == NULL)
		return (0);
	while (lxd[s])
	{
		i = 0;
		while (lxd[s] && lxd[s][i])
		{
			if (ft_isredirect(lxd[s][i]) == TRUE || lxd[s][i] == '|')
				if (count_specials(lxd[s], lxd[s][i]) == FAILURE)
					return (FALSE);
			if (ft_isredirect(lxd[s][i]) == TRUE
					&& lxd[s + 1] && ft_isredirect(lxd[s + 1][i]) == TRUE)
				return (unexpected_token(&lxd[s + 1][i]), FALSE);
			if (lxd[s][i])
				i++;
		}
		s++;
	}
	return (TRUE);
}

/**
 * @brief checks whether lxd contains a valid amount of specials
 * 
 * @param lxd - trimmed string of the user's input
 * @param c - special character that is currently looked at
 * @return int - true or false
 */
static int	count_specials(char *lxd, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (lxd[i] && lxd[i] == c)
	{
		cnt++;
		i++;
	}
	if (cnt >= 2)
		return (print_invalid_num_of_specials(c, cnt));
	return (SUCCESS);
}

/**
 * @brief prints the appropriate error message
 * (depending on the amount of specials and the kind of special character)
 * 
 * @param c - special character
 * @param cnt - invalid amount of specials
 * @return int - true or false
 */
static int	print_invalid_num_of_specials(char c, int cnt)
{
	if (c == '<' && cnt == 3)
		unexpected_token("<");
	else if (c == '<' && cnt > 3)
		unexpected_token("<<");
	else if (c == '>' && cnt == 3)
		unexpected_token(">");
	else if (c == '>' && cnt > 3)
		unexpected_token(">>");
	else if (c == '|' && cnt == 2)
		unexpected_token("|");
	else if (c == '|' && cnt > 2)
		unexpected_token("||");
	else
		return (SUCCESS);
	return (FAILURE);
}
