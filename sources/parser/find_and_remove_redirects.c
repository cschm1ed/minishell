/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_remove_redirects.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:53:39 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/24 20:46:56 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                        				:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:40:48 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/02 16:40:48 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redirect(t_list *tokens, t_list **head, t_list **redirect,
				t_info *info);
static int	set_mode(t_list *tokens, t_list **head, t_list **add,
				t_info *info);

/**
 * @brief checks token list for redirect '>' or delimiter '<' symbols
 * 			and stores information in the parsed struct accordingly.
 * 			Said tokens are removed afterwards.
 *
 * @param tokens - the beginning of the token list
 * @param parsed - the struct into which information should be stored
 * @return - returns FAILURE in case of an error otherwise SUCCESS
 */
int	redirects(t_list **tokens, t_parsed *parsed, t_info *info)
{
	t_list	*ptr;

	if (tokens == NULL || *tokens == NULL)
		return (SUCCESS);
	ptr = *tokens;
	while (ptr && ft_strcmp(ptr->content, "|") != 0)
	{
		if (ft_strcmp(ptr->content, ">") == 0)
		{
			if (redirect(ptr, tokens,
					&(parsed->redirect_output), info) == FAILURE)
				return (FAILURE);
			ptr = *tokens;
		}
		else if (ft_strcmp((char *)ptr->content, "<") == 0)
		{
			if (redirect(ptr, tokens,
					&(parsed->redirect_input), info) == FAILURE)
				return (FAILURE);
			ptr = *tokens;
		}
		else
			ptr = ptr->next;
	}
	return (SUCCESS);
}

static int	redirect(t_list *tokens, t_list **head, t_list **redirect,
					t_info *info)
{
	t_list	*tmp;
	t_list	*node;
	char	*name;

	if (tokens->next == NULL)
		return (unexpected_token("newline"));
	else if (ft_isspecial(*tokens->next->content))
		return (unexpected_token(tokens->next->content));
	name = ft_strdup(tokens->next->content);
	if (name == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	node = lst_newvar_node(NULL, name, REDIRECT);
	if (node == NULL)
	{
		free(name);
		exit_error(info, __FILE__, __LINE__, "malloc");
	}
	ft_lstadd_back(redirect, node);
	tmp = tokens;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}

/**
 * @brief checks token list for append '>>' or delimiter '<<' symbols
 * 			and stores information in the parsed struct accordingly.
 * 			Said tokens are removed afterwards.
 *
 * @param tokens - the beginning of the token list
 * @param parsed - the struct into which information should be stored
 * @return - returns FAILURE in case of an error otherwise SUCCESS
 */
int	delimiter_and_append(t_list **tokens, t_parsed *parsed, t_info *info)
{
	t_list	*ptr;

	if (tokens == NULL || *tokens == NULL)
		return (SUCCESS);
	ptr = *tokens;
	while (ptr && ft_strcmp(ptr->content, "|") != 0)
	{
		if (ft_strcmp((char *)ptr->content, ">>") == 0)
		{
			if (set_mode(ptr, tokens,
					&(parsed->redirect_output), info) == FAILURE)
				return (FAILURE);
			ptr = *tokens;
		}
		else if (ft_strcmp((char *)ptr->content, "<<") == 0)
		{
			if (set_mode(ptr, tokens, &(parsed->here_docs), info) == FAILURE)
				return (FAILURE);
			ptr = *tokens;
		}
		else
			ptr = ptr->next;
	}
	return (SUCCESS);
}

static int	set_mode(t_list *tokens, t_list **head, t_list **add, t_info *info)
{
	t_list	*tmp;
	t_list	*node;
	char	*name;

	if (tokens->next == NULL)
		return (unexpected_token(NULL));
	else if (ft_isspecial(*tokens->next->content) == TRUE)
		return (unexpected_token(tokens->next->content));
	name = ft_strdup(tokens->next->content);
	if (name == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	node = lst_newvar_node(NULL, name, 1);
	if (node == NULL)
	{
		free(name);
		exit_error(info, __FILE__, __LINE__, "malloc");
	}
	ft_lstadd_back(add, node);
	tmp = tokens;
	ft_lstrmone(head, tmp->next, free);
	ft_lstrmone(head, tmp, free);
	return (SUCCESS);
}
