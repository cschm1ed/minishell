/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_and_append.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:01:15 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/02 17:01:15 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_append(t_list *tokens, t_parsed *parsed, t_list **head);
static int	set_delimiter(t_list *tokens, t_parsed *parsed, t_list **head);

int	delimiter_and_append(t_list **tokens, t_parsed *parsed)
{
	t_list	*ptr;

	if (tokens == NULL || *tokens == NULL)
		return (SUCCESS);
	ptr = *tokens;
	while (ptr && ft_strcmp(ptr->content, "|") != 0)
	{
		if (ft_strcmp((char *)ptr->content, ">>") == 0)
		{
			if (set_append(*tokens, parsed, tokens) == FAILURE)
				return (FAILURE);
			ptr = *tokens;
		}
		else if (ft_strcmp((char *)ptr->content, "<<") == 0)
		{
			if (set_delimiter(ptr, parsed, tokens) == FAILURE)
				return (FAILURE);
			ptr = *tokens;
		}
		else
			ptr = ptr->next;
	}
	return (SUCCESS);
}

static int	set_delimiter(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list	*tmp;

	if (tokens->next == NULL)
		return (printf
			("minishell: syntax error near unexpected token `newline'\n"),
			FAILURE);
	parsed->delimiter = (char *)tokens->next->content;
	tmp = tokens;
	tokens = tokens->next->next;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}

static int	set_append(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list	*tmp;

	if (tokens->next == NULL)
		return (printf
			("minishell: syntax error near unexpected token `newline'\n"),
			FAILURE);
	parsed->redirect_input = (char *)tokens->next->content;
	parsed->append_mode = TRUE;
	tmp = tokens;
	tokens = tokens->next->next;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}
