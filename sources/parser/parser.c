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
			return (NULL);
		tokens = tokens->next;
	}
	return (current);
}

int	test_parser(void)
{
	char		*input[] = {"<", "infile", "cat",
							"-e", "|", "wc", "-l", ">", "outfile", NULL};
	t_parsed	*parsed;
	int			i;

	i = 0;
	printf("input: ");
	while (input[i])
		printf("%s ",input[i++]);
	printf("\n");
	parsed = parser(NULL, &parsed, input);
	if (!parsed)
		return (FAILURE);
	print_parsed(parsed);
	return (SUCCESS);
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
		printf("Node %d:\n", i);
		printf("cmd:\n\t%s\n", parsed->cmd);
		j = 0;
		if (parsed->args)
		{
			printf("args:\n");
			while (parsed->args[j])
			{
				printf("\t%s, ", parsed->args[j]);
				j ++;
			}
		}
		printf("\n");
		printf("redirect input:\n\t%s\n", parsed->redirect_input);
		printf("redirect output:\n\t%s\n", parsed->redirect_output);
		printf("delimiter:\n\t%s\n", parsed->delimiter);
		printf("append mode:\n\t%d\n\n", parsed->append_mode);
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
