/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_remove_delimiter_and_append.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:01:15 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/02 17:01:15 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list *set_append(t_list *tokens, t_parsed *parsed, t_list **head);
static t_list *set_delimiter(t_list *tokens, t_parsed *parsed, t_list **head);

void	*find_and_remove_delimiter_and_append(t_list *tokens, t_parsed *parsed)
{
	t_list	**head;

	head = &tokens;
	while (tokens)
	{
		if (ft_strcmp((char *)tokens->content, ">>") == 0)
		{
			tokens = set_append(tokens, parsed, head);
			if (tokens == NULL)
				return (NULL);
		}
		else if (ft_strcmp((char *)tokens->content, "<<") == 0)
		{
			tokens = set_delimiter(tokens, parsed, head);
			if (tokens == NULL)
				return (NULL);
		}
		else
			tokens = tokens->next;
	}
	return ((void*)(*head));
}

static t_list *set_delimiter(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list *tmp;

	if (tokens->next == NULL)
		printf("minishell: syntax error near unexpected token `newline'\n");
	parsed->delimiter = (char *)tokens->next->content;
	tmp = tokens;
	tokens = tokens->next->next;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return tokens;
}


static t_list *set_append(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list *tmp;

	if (tokens->next == NULL)
		printf("minishell: syntax error near unexpected token `newline'\n");
	parsed->redirect_input = (char *)tokens->next->content;
	parsed->append_mode = TRUE;
	tmp = tokens;
	tokens = tokens->next->next;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return tokens;
}
