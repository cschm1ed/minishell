/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:26:15 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/25 13:18:30 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_search_for_char(char *s, size_t *i, char c)
{
	if (c == '"' || c == '\'' || c == '>' || c == '<')
		(*i)++;
	while (s[*i] != c && s[*i])
		(*i)++;
}

static int	ft_cnt_sub_cmds(char *s)
{
	size_t	i;
	int		cnt;

	i = -1;
	cnt = 1;
	while (s[++i])
	{
		if (s[i] == ' ' || s[i] == '>' || s[i] == '<')
		{
			ft_search_for_char(s, &i, s[i]);
			cnt++;
		}
		if (s[i] == '"' || s[i] == '\'')
			ft_search_for_char(s, &i, s[i]);
	}
	return (cnt);
}

static void	ft_locate_substr(char *s, size_t *start, size_t *len)
{
	while (s[(*start)] == ' ' && s[(*start)])
		(*start)++;
	(*len) = (*start);
	if (s[(*len)] == '"' || s[(*len)] == '\'')
	{
		ft_search_for_char(s, len, s[(*len)]);
		(*start)++;
	}
	else if (s[(*len)] == '>' && ft_isspace(s[(*len + 1)]) == FAILURE)
		*len += 1;
	else
		ft_search_for_char(s, len, ' ');
}

static int	ft_check_syntax(char *cmd)
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
		return (FAILURE);
	return (SUCCESS);
}

char	**lexer(char *cmd)
{
	char	**substr;
	int		sub_cmds;
	size_t	start;
	size_t	len;

	if (*cmd == 0 || !cmd)
		return (NULL);
	else if (ft_check_syntax(cmd) == FAILURE)
		return (printf("Invalid syntax\n"), NULL);
	substr = malloc(sizeof(char *) * (ft_cnt_sub_cmds(cmd) + 1));
	if (substr == NULL)
		return (NULL);
	sub_cmds = 0;
	start = 0;
	while (sub_cmds < ft_cnt_sub_cmds(cmd))
	{
		ft_locate_substr(cmd, &start, &len);
		substr[sub_cmds] = ft_substr(cmd, start, len - start);
		if (!substr[sub_cmds])
			return (ft_free_dbl_ptr(substr));
		sub_cmds++;
		start = len;
	}
	substr[sub_cmds] = NULL;
	return (substr);
}
