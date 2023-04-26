/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:26:15 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/26 14:50:51 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_search_for_char(char *s, size_t *i, char c)
{
	if (c == '"' || c == '\'')
		(*i)++;
	while (s[*i] != c && s[*i] && s[*i] != '>' && s[*i] != '<')
		(*i)++;
}

static int ft_search_for_redirection(char *s, size_t *i)
{
	if (s[*i] == '>' || s[*i] == '<')
	{
		while ((s[*i] == '>' && s[*i + 1] == '>' || s[*i + 1] == '<')
			|| (s[*i] == '<' && s[*i + 1] == '<' || s[*i + 1] == '>'))
			(*i)++;
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	ft_cnt_sub_cmds(char *s)
{
	size_t	i;
	int		cnt;

	i = -1;
	cnt = 1;
	while (s[++i])
	{
		// printf("INDEX: %c[%zu]\n", s[i], i);
		if (s[i] == ' ' || s[i] == '>' || s[i] == '<'
			|| s[i - 1] == '>' || s[i - 1] == '<')
		{
			while (s[i] == ' ')
 				i++;
			if (ft_search_for_redirection(s, &i) == FAILURE)
				ft_search_for_char(s, &i, s[i]);
			cnt++;
		}
		if (s[i] == '"' || s[i] == '\'')
			ft_search_for_char(s, &i, s[i]);
	}
	return (cnt);
}

static int	ft_locate_substr(char *s, size_t *start, size_t *len)
{
	while (s[(*start)] == ' ' && s[(*start)])
		(*start)++;
	(*len) = (*start);
	while (s[(*len)] == '>' || s[(*len)] == '<')
	{
		*len += 1;
		if ((s[(*len)] != '>' && s[(*len)] != '<'))
			return (SUCCESS);
	}
	if (s[(*len)] == '"' || s[(*len)] == '\'')
	{
		ft_search_for_char(s, len, s[(*len)]);
		(*start)++;
	}
	else
		ft_search_for_char(s, len, ' ');
	return (SUCCESS);
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
		return (printf("minishell: syntax error near unexpected token\n"), FAILURE);
	return (SUCCESS);
}

char	**lexer(char *cmd)
{
	char	**substr;
	int		sub_cmds;
	size_t	start;
	size_t	len;

	if (*cmd == 0 || !cmd || ft_check_syntax(cmd) == FAILURE)
		return (NULL);
	substr = (char **) malloc (sizeof(char *) * (ft_cnt_sub_cmds(cmd) + 1));
	if (substr == NULL)
		return (perror("malloc"), NULL);
	sub_cmds = 0;
	start = 0;
	//printf(GREEN"Count: %d\n"ESC, ft_cnt_sub_cmds(cmd));
	while (sub_cmds < ft_cnt_sub_cmds(cmd))
	{
		ft_locate_substr(cmd, &start, &len);
		substr[sub_cmds] = ft_substr(cmd, start, len - start);
		if (!substr[sub_cmds])
			return (ft_free_dbl_ptr(substr));
		//printf(PURPLE"String: "ESC"%s\n", substr[sub_cmds]);
		sub_cmds++;
		start = len;
	}
	substr[sub_cmds] = NULL;
	return (substr);
}
