/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:33:16 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/12 16:37:37 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parse_command(t_list **p_lst, t_list *t_start, t_info *info);
static int distribute_commands(t_list **parsed, t_info *info);

/**
 * Takes a list of tokens created by the lexer, and fills one parsed struct
 * for each command found in the token list.
 *
 * @param info - general info struct
 * @param parsed - list of parsed struct that sould be filled
 * @param lexed - list of tokens generated by the lexer
 *
 * @return - NULL in case of an error
 */
t_list	*parser(t_list **parsed, char **lexed, t_info *info)
{
	*parsed = NULL;
	info->token_lst = str_arr_to_lst(lexed);
	if (info->token_lst == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	if (distribute_commands(parsed, info) == FAILURE)
		return (*parsed);
	return (*parsed);
}

static int distribute_commands(t_list **parsed, t_info *info)
{
	int		first;
	t_list	*node;

	node = info->token_lst;
	first = TRUE;
	while (node)
	{
		if (ft_strcmp(node->content, "|") != 0 && first == TRUE)
		{
			if (parse_command(parsed, node, info) == FAILURE)
				return (FAILURE);
		}
		else if (ft_strcmp(node->content, "|") == 0)
		{
			if (first == TRUE)
				return (unexpected_token("|"));
			else if (parse_command(parsed, node->next, info) == FAILURE)
				return (FAILURE);
		}
		first = FALSE;
		if (node == NULL)
			return (SUCCESS);
		node = node->next;
	}
	return (SUCCESS);
}

static int	parse_command(t_list **p_lst, t_list *t_start, t_info *info)
{
	t_list		*node;

	node = lst_newparsed_node();
	if (node == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	ft_lstadd_back(p_lst, node);
	if (t_start == NULL)
		return (unexpected_token("|"), FAILURE);
	redirects(t_start, lst_get_parsed(node), info);
	add_args(node, info, t_start);
	return (SUCCESS);
}
