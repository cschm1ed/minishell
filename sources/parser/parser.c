/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:33:16 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/07 17:16:15 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_list	*parse_command(t_list **p_lst, t_list *t_start, t_info *info);
static int		distribute_commands(t_list **parsed, t_info *info);
static t_list	*add_redirect(t_list *t_start, t_info *info, t_list *node,
					t_list *parsed);

/**
 * Takes a list of tokens created by the lexer, and fills one parsed struct
 * for each command found in the token list.
 *
 * @param info - general info struct
 * @param parsed - list of parsed struct that should be filled
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
		return (NULL);
	return (*parsed);
}

static int	distribute_commands(t_list **parsed, t_info *info)
{
	int		first;
	t_list	*node;

	first = TRUE;
	node = info->token_lst;
	while (node)
	{
		if (first == TRUE && !ft_strcmp(node->content, "|")
            && !is_literal(node, info))
			return (unexpected_token("|"));
		if ((!is_literal(node, info) && !ft_strcmp(node->content, "|"))
                || first == TRUE)
		{
			node = parse_command(parsed, node, info);
			if (node == NULL)
				return (FAILURE);
		}
		first = FALSE;
		if (node == NULL)
			return (SUCCESS);
		node = node->next;
	}
	return (SUCCESS);
}

static t_list	*parse_command(t_list **p_lst, t_list *t_start, t_info *info)
{
	t_list	*parsed;

	parsed = lst_newparsed_node();
	if (parsed == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	ft_lstadd_back(p_lst, parsed);
	if (t_start == NULL)
		return (unexpected_token("|"), NULL);
	if (ft_strcmp(t_start->content, "|") == 0 && !is_literal(t_start, info))
		return (add_redirect(t_start->next, info, t_start->next, parsed));
	else
		return (add_redirect(t_start, info, info->token_lst, parsed));
}

static t_list	*add_redirect(t_list *t_start, t_info *info, t_list *node,
			t_list *parsed)
{
	if (t_start == NULL)
		return (node);
	if (t_start->next == NULL && (!is_literal(t_start, info)
            && (invalid_special(t_start->content) == TRUE
			|| invalid_colon(t_start->content) == TRUE)))
		return (NULL);
	redirects(t_start, lst_get_parsed(parsed), info);
	add_args(parsed, info, node);
	return (node);
}
