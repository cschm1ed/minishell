/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/22 17:57:46 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_specials(char *lxd, int *i, char c);
static void	print_invalid_num_of_specials(char c, int cnt);

int	valid_num_of_quotes(char *cmd, t_info *info)
{
	size_t	i;
	char	quote;

	i = -1;
	while (cmd[++i])
	{
		if (ft_isquote(cmd[i]) == TRUE)
		{
			quote = cmd[i];
			if (skip_until_quote(cmd, &i) == FALSE)
				return (unexpected_token(&quote), info->exit_code = 258, FALSE);
		}
	}
	return (TRUE);
}

/**
 * @brief checks if the lexed array only contains valid specials ('>' '<' '|')
 * @param lxd the lexed array of the user's cmd
 * @return true or false
 */
int	valid_num_of_specials(char **lxd, t_info *info)
{
	int	s;
	int	i;

	s = -1;
	while (lxd[++s])
	{
		i = -1;
		while (lxd[s] && lxd[s][++i])
		{
			if (ft_isredirect(lxd[s][i]) == TRUE || lxd[s][i] == '|')
				if (count_specials(lxd[s], &i, lxd[s][i]) == FAILURE)
					return (info->exit_code = 258, FALSE);
			if (lxd[s + 1] && ft_isredirect(lxd[s][i] == TRUE)
				&& ft_isredirect(lxd[s + 1][i]) == TRUE)
				return (unexpected_token(&lxd[s + 1][i]),
					info->exit_code = 258, FALSE);
		}
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
static int	count_specials(char *lxd, int *i, char c)
{
	int	cnt;

	cnt = 0;
	while (lxd[(*i)] && lxd[(*i)] == c)
	{
		if ((c == '>' && lxd[(*i)] == '<')
			|| (c == '<' && lxd[(*i)] == '>'))
			return (3);
		cnt++;
		(*i)++;
	}
	if (cnt >= 3)
		return (print_invalid_num_of_specials(c, cnt), FAILURE);
	return (SUCCESS);
}

static void	print_invalid_num_of_specials(char c, int cnt)
{
	if (c == '<' && cnt == 3)
		unexpected_token("<");
	else if (c == '<' && cnt > 3)
		unexpected_token("<<");
	else if (c == '>' && cnt == 3)
		unexpected_token(">");
	else if (c == '>' && cnt > 3)
		unexpected_token(">>");
	else if (c == '|' && cnt == 3)
		unexpected_token("|");
	else if (c == '|' && cnt > 3)
		unexpected_token("||");
}
