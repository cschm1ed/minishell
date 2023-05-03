/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_remove_redirects.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:40:48 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/02 16:40:48 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list *redirect_input(t_list *tokens, t_parsed *parsed, t_list **head);
static t_list *redirect_output(t_list *tokens, t_parsed *parsed, t_list **head);

void	*find_and_remove_redirects(t_list *tokens, t_parsed *parsed)
{
	t_list	**head;

	head = &tokens;
	while (tokens)
	{
		if (ft_strcmp((char *)tokens->content, ">") == 0)
		{
			tokens = redirect_input(tokens, parsed, head);
			if (tokens == NULL)
				return (NULL);
		}
		else if (ft_strcmp((char *)tokens->content, "<") == 0)
		{
			tokens = redirect_output(tokens, parsed, head);
			if (tokens == NULL)
				return (NULL);
		}
		else
			tokens = tokens->next;
	}
	return ((void *)(*head));
}

static t_list *redirect_output(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list *tmp;

	if (tokens->next == NULL)
		printf("minishell: syntax error near unexpected token `newline'\n");
	parsed->redirect_input = (char *)tokens->next->content;
	tmp = tokens;
	tokens = tokens->next->next;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return tokens;
}

static t_list *redirect_input(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list *tmp;

	if (tokens->next == NULL)
		printf("minishell: syntax error near unexpected token `newline'\n");
	parsed->redirect_output = (char *)tokens->next->content;
	tmp = tokens;
	tokens = tokens->next->next;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return tokens;
}
