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

static void *parse_command(t_parsed **head, t_list **begin);

void	print_linked_lst(t_list *lst);

t_parsed *parser(t_info *info, t_parsed **parsed, char **lexed)
{
	t_list	*token_lst;
	t_list	*tmp_begin;
	t_list	*tmp;
	int 	first;

	first = TRUE;
	*parsed = NULL;
	token_lst = str_arr_to_lst(lexed);
	if (token_lst == NULL)
		return (perror("parser got no token lst\n"), NULL);
	replace_variables(info, token_lst);
	tmp_begin = token_lst;
	if (ft_lstsize(token_lst) == 1)
	{
		*parsed = ft_calloc(1, sizeof(t_parsed));
		(*parsed)->cmd = token_lst->content;
		return (*parsed);
	}
	while (token_lst && token_lst->next)
	{
		if (first == TRUE)
		{
			parse_command(parsed, &token_lst);
			first = FALSE;
		}
		else if (ft_strcmp((char *)token_lst->next->content, "|") == 0)
		{
			tmp = token_lst->next;
			token_lst->next = NULL;
			if (tmp->next)
				tmp_begin = tmp->next;
			else
				tmp_begin = NULL; // error missing
			parse_command(parsed, &tmp_begin);
		}
		token_lst = token_lst->next;
	}
	return (*parsed);
}

static void *parse_command(t_parsed **head, t_list **begin)
{
	t_parsed	*current;
	t_parsed	*ptr;
	t_list		*tokens;

	current = ft_calloc(1, sizeof(t_parsed));
	if (!current)
	{
		return (perror("malloc"), NULL);
	}
	if (!*head)
		*head = current;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = current;
	}
	if (find_and_remove_redirects(begin, current) == FAILURE)
		return (printf("failed on redirects\n"), NULL); // add appropriate free of current in future
	if (find_and_remove_delimiter_and_append(begin, current) == FAILURE)
		return (printf("failed on delimiters\n"), NULL);
	tokens = *begin;
	current->cmd = tokens->content;
	tokens = tokens->next;
	while (tokens && ft_strcmp(tokens->content, "|") != 0)
	{
		if (str_arr_add(&(current->args), tokens->content) == NULL)
			return (perror("failed to create array\n"), NULL);
		tokens = tokens->next;
	}
	return (current);
}

void	print_parsed(t_parsed *parsed)
{
	int	i;
	int	j;

	i = 0;
	if (parsed == NULL)
		printf("parsed does not exist\n");
	while (parsed)
	{
		printf(YELLOW"Node %d:\n"ESC, i);
		printf(GREEN"cmd:\t%s\n"ESC, parsed->cmd);
		j = 0;
		if (parsed->args)
		{
			printf(GREEN"args:"ESC);
			while (parsed->args[j])
			{
				printf(GREEN"\t%s, "ESC, parsed->args[j]);
				j ++;
			}
		}
		printf("\n");
		printf(GREEN"redirect input:\t%s\n"ESC, parsed->redirect_input);
		printf(GREEN"redirect output:\t%s\n"ESC, parsed->redirect_output);
		printf(GREEN"delimiter:\t%s\n"ESC, parsed->delimiter);
		printf(GREEN"append mode:\t%d\n\n"ESC, parsed->append_mode);
		parsed = parsed->next;
		i ++;
	}
}

void	print_linked_lst(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char*)lst->content);
		lst = lst->next;
	}
}
