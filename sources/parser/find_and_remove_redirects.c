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

	if (tokens->next == NULL)
		return (unexpected_token("newline"));
	parsed->redirect_output = ft_strdup(tokens->next->content);
	if (parsed->redirect_output == NULL)
		return (perror("malloc"), FAILURE);
	tmp = tokens;
	tokens = tokens->next->next;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}

static int	redirect_input(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list	*tmp;

	if (tokens->next == NULL)
		return (unexpected_token("newline"));
	parsed->redirect_input = ft_strdup(tokens->next->content);
	if (parsed->redirect_input == NULL)
		return (perror("malloc"), FAILURE);
	tmp = tokens;
	tokens = tokens->next->next;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}
