/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:33:16 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 17:16:14 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_command(t_list **p_lst, t_list **t_start);
static int	distribute_commands(t_list **token_lst, t_list **parsed);
static int	add_args(t_list	**t_start, t_list *node);

t_list	*parser(t_info *info, t_list **parsed, char **lexed)
{
	t_list	*token_lst;

	*parsed = NULL;
	token_lst = str_arr_to_lst(lexed);
	if (token_lst == NULL)
		return (perror("parser got no token lst\n"), NULL);
	replace_variables(info, token_lst);
	if (distribute_commands(&token_lst, parsed) == FAILURE)
		return (NULL);
	return (*parsed);
}

static int	distribute_commands(t_list **token_lst, t_list **parsed)
{
	int		first;
	t_list	*node;

	node = *token_lst;
	first = TRUE;
	while (node)
	{
		if (ft_strcmp(node->content, "|") != 0 && first == TRUE)
		{
			if (parse_command(parsed, &node) == FAILURE)
				return (FAILURE);
		}
		else if (ft_strcmp(node->content, "|") == 0)
		{
			if (first == TRUE)
				return (unexpected_token("|"));
			else if (parse_command(parsed, &(node->next)) == FAILURE)
				return (FAILURE);
		}
		first = FALSE;
		if (node == NULL)
			return (SUCCESS);
		node = node->next;
	}
	return (SUCCESS);
}

static int	parse_command(t_list **p_lst, t_list **t_start)
{
	t_list		*node;

	node = lst_newparsed_node();
	if (node == NULL)
		return (FAILURE);
	ft_lstadd_back(p_lst, node);
	if (t_start == NULL)
		return (unexpected_token("|"));
	if (redirects(t_start, lst_get_parsed(node)) == FAILURE
		|| delimiter_and_append(t_start, lst_get_parsed(node)) == FAILURE)
		return (FAILURE);
	if (add_args(t_start, node) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	add_args(t_list **t_start, t_list *node)
{
	t_list		*args;

	args = *t_start;
	if (args != NULL)
	{
		lst_get_parsed(node)->cmd = args->content;
		args = args->next;
	}
	while (args && ft_strcmp(args->content, "|") != 0)
	{
		if (str_arr_add(&(lst_get_parsed(node)->args), args->content) == NULL)
			return (FAILURE);
		args = args->next;
	}
	return (SUCCESS);
}
