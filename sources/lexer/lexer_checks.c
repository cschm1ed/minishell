/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/30 13:44:10 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_specials(char *lxd, char c);
static int	print_invalid_num_of_specials(char c, int cnt);

int	invalid_colon(char *cmd)
{
	int	i;
	int	colon;

	colon = 0;
	i = 0;
	while (cmd[i] && (ft_isspace(cmd[i]) || cmd[i] == ':'))
	{
		if (cmd[i] == ':')
			colon++;
		i++;
	}
	if (!cmd[i] && colon == 1)
		return (g_exit_code = 0, TRUE);
	return (FALSE);
}

int	invalid_special(char *cmd)
{
	int	i;
	int	special;

	special = 0;
	i = 0;
	while (cmd[i]
		&& (ft_isspace(cmd[i]) || ft_isspecial(cmd[i]) || cmd[i] == '!'))
	{
		if (ft_isspecial(cmd[i]) || cmd[i] == '!')
			special++;
		i++;
	}
	if (!cmd[i] && special >= 1)
		return (g_exit_code = 258, unexpected_token("newline"), TRUE);
	return (FALSE);
}

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
