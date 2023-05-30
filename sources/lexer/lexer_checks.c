/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/29 18:02:49 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_specials(char *lxd, char c);
static int	print_invalid_num_of_specials(char c, int cnt);

int	valid_num_of_quotes(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (ft_isquote(cmd[i]) == TRUE)
		{
			if (skip_until_quote(cmd, &i) == FALSE)
				return (printf(SYNERR), g_exit_code = 258, FALSE);
		}
	}
	return (TRUE);
}

/**
 * @brief checks if the lexed array only contains valid specials ('>' '<' '|')
 * @param lxd the lexed array of the user's cmd
 * @return true or false
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
			if (lxd[s][i] == '>' && lxd[s + 1] && lxd[s + 1][i] == '<')
				return (unexpected_token(&lxd[s + 1][i]), FALSE);
			if (lxd[s][i])
				i++;
		}
		s++;
	}
	return (TRUE);
}

/**
 * @brief counts how many special characters are contained and their syntax
 * @param lxd string that contains a special character
 * @param i index to continue interating through the user's input
 * @param c special character
 * @return int 
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
