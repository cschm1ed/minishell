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

#include <minishell.h>

static int	set_append(t_list *tokens, t_parsed *parsed, t_list **head);
static int	set_delimiter(t_list *tokens, t_parsed *parsed, t_list **head);

/**
 * @brief checks token list for append '>>' or delimiter '<<' symbols
 * 			and stores information in the parsed struct accordingly.
 * 			Said tokens are removed afterwards.
 *
 * @param tokens - the beginning of the token list
 * @param parsed - the struct into which information should be stored
 * @return - returns FAILURE in case of an error otherwise SUCCESS
 */
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
			if (set_append(ptr, parsed, tokens) == FAILURE)
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
	t_list	*node;
	char	*name;

	if (tokens->next == NULL)
		return (printf
			("minishell: syntax error near unexpected token `newline'\n"),
			FAILURE);
	name = ft_strdup(tokens->next->content);
	if (name == NULL)
		return (FAILURE);
	node = lst_newvar_node(NULL, name, DELIMITER);
	if (node == NULL)
		return (free(name), FAILURE);
	ft_lstadd_back(&(parsed->redirect_input), node);
	tmp = tokens;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}

static int	set_append(t_list *tokens, t_parsed *parsed, t_list **head)
{
	t_list	*tmp;
	t_list	*node;
	char 	*name;

	if (tokens->next == NULL)
		return (printf
			("minishell: syntax error near unexpected token `newline'\n"),
			FAILURE);
	name = ft_strdup(tokens->next->content);
	if (name == NULL)
		return (FAILURE);
	node = lst_newvar_node(NULL, name, APPEND);
	if (node == NULL)
		return (free(name), FAILURE);
	ft_lstadd_back(&(parsed->redirect_output), node);
	parsed->append_mode = TRUE;
	tmp = tokens;
	tokens = tokens->next->next;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}
