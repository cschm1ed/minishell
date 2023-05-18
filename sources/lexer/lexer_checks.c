/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/03 18:01:25 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_specials(char *lxd, int *i, char c);

int	valid_num_of_quotes(char *cmd, t_info *info)
{
	size_t	i;

	i = -1;
	while (cmd[++i])
		if (ft_isquote(cmd[i]))
			if (!skip_until_quote(cmd, &i))
				return (printf(SYNERR), info->exit_code = 258, FALSE);
	return (TRUE);
}

// /**
//  * @brief checks if the user's cmd contains an even number of quotation marks
//  * @param cmd the user's input that was read from the line
//  * @return true or false
//  */
// int	valid_num_of_quotes(char *cmd, t_info *info)
// {
// 	int		dbl_qte;
// 	int		sng_qte;
// 	int		i;

// 	dbl_qte = 0;
// 	sng_qte = 0;
// 	i = -1;
// 	while (cmd[++i])
// 	{
// 		if (cmd[i] == '"')
// 			dbl_qte++;
// 		else if (cmd[i] == '\'')
// 			sng_qte++;
// 	}
// 	if (dbl_qte % 2 != 0 || sng_qte % 2 != 0)
// 		return (printf(SYNERR), info->exit_code = 258, FALSE);
// 	return (TRUE);
// }

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
		while (lxd[s][++i])
		{
			if (lxd[s + 1] && ft_isredirect(lxd[s][i])
				&& ft_isredirect(lxd[s + 1][i]))
				return (printf(SYNERR), info->exit_code = 258, FALSE);
			if (ft_isredirect(lxd[s][i]) || lxd[s][i] == '|')
				if (count_specials(lxd[s], &i, lxd[s][i]) > 2)
					return (printf(SYNERR), info->exit_code = 258, FALSE);
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
	while (lxd[(*i)] && lxd[(*i)++] == c)
	{
		if ((c == '>' && lxd[(*i)] == '<')
			|| (c == '<' && lxd[(*i)] == '>'))
			return (3);
		cnt++;
	}
	return (cnt);
}
