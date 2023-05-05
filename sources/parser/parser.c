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

static int	parse_command(t_parsed **p_lst, t_list **t_start);
static void	parsed_add_back(t_parsed **head, t_parsed *new_node);
static int	distribute_commands(t_list **token_lst, t_parsed **parsed);

t_parsed *parser(t_info *info, t_parsed **parsed, char **lexed)
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

static int distribute_commands(t_list **token_lst, t_parsed **parsed)
{
	int 	first;
	t_list	*node;

	node = *token_lst;
	first = TRUE;
	printf("distributing\n");
	while (node)
	{
		if (ft_strcmp(node->content, "|") == 0)
		{
			if (first == TRUE)
				return (printf("minishell: syntax error near unexpected token `|'\n"), FAILURE);
			else if (parse_command(parsed, &(node->next)) == FAILURE)
				return (perror("parsing failed"), FAILURE);
		}
		else if (ft_strcmp(node->content, "|") != 0 && first == TRUE)
		{
			if (parse_command(parsed, &node) == FAILURE)
				return (perror("parsing failed"), FAILURE);
		}
		first = FALSE;
		if (node)
			node = node->next;
		else
			return (SUCCESS); // case with only redirect as input e.g "< infile"
	}
	return (SUCCESS);
}

static int parse_command(t_parsed **p_lst, t_list **t_start)
{
	t_parsed	*current;
	t_list 		*args;

	current = ft_calloc(1, sizeof(t_parsed));
	if (current == NULL)
		return (perror("malloc"), FAILURE);
	parsed_add_back(p_lst, current);
	if (t_start == NULL)
		return (printf("minishell: syntax error near unexpected token `|'\n"), FAILURE);
	if (find_and_remove_redirects(t_start, current) == FAILURE
		|| find_and_remove_delimiter_and_append(t_start, current) == FAILURE)
		return (FAILURE);
	args = *t_start;
	if (args != NULL)
	{
		current->cmd = args->content;
		args = args->next;
	}
	while (args && ft_strcmp(args->content, "|") != 0)
	{
		if (str_arr_add(&(current->args), args->content) == NULL)
			return (FAILURE);
		args = args->next;
	}
	return (SUCCESS);
}

static	void	parsed_add_back(t_parsed **head, t_parsed *new_node)
{
	t_parsed	*ptr;

	if (!*head)
		*head = new_node;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}
