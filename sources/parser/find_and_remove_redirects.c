/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:40:48 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/02 16:40:48 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_input(t_list *tokens, t_parsed *parsed, t_list **head);
static int	redirect_output(t_list *tokens, t_parsed *parsed, t_list **head);

/**
 * @brief checks token list for redirect '>' or delimiter '<' symbols
 * 			and stores information in the parsed struct accordingly.
 * 			Said tokens are removed afterwards.
 *
 * @param tokens - the beginning of the token list
 * @param parsed - the struct into which information should be stored
 * @return - returns FAILURE in case of an error otherwise SUCCESS
 */
int	redirects(t_list **tokens, t_parsed *parsed)
{
	t_list	*ptr;

	if (tokens == NULL || *tokens == NULL)
		return (SUCCESS);
	ptr = *tokens;
	while (ptr && ft_strcmp(ptr->content, "|") != 0)
	{
		if (ft_strcmp(ptr->content, ">") == 0)
		{
			if (redirect_output(ptr, parsed, tokens) == FAILURE)
				return (FAILURE);
			ptr = *tokens;
		}
		else if (ft_strcmp((char *)ptr->content, "<") == 0)
		{
			if (redirect_input(ptr, parsed, tokens) == FAILURE)
				return (FAILURE);
			ptr = *tokens;
		}
		else
			ptr = ptr->next;
	}
	return (SUCCESS);
}

static int	redirect_output(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list	*tmp;
	t_list	*node;

	if (tokens->next == NULL)
		return (unexpected_token("newline"));
	node = ft_lstnew(tokens->next->content);
	if (node == NULL)
		return (FAILURE);
	ft_lstadd_back(&(parsed->redirect_output), node);
	if (parsed->redirect_output == NULL)
		return (perror("malloc"), FAILURE);
	tmp = tokens;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}

static int	redirect_input(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list	*tmp;

	if (tokens->next == NULL)
		return (unexpected_token("newline"));
	ft_lstlast(parsed->redirect_input)->content = ft_strdup(tokens->next->content);
	if (parsed->redirect_input == NULL)
		return (perror("malloc"), FAILURE);
	tmp = tokens;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}
