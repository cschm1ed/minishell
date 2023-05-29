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

#include <minishell.h>

void redirects(t_list *tokens, t_parsed *parsed, t_info *info)
{
	t_list	*ptr;

	if (tokens == NULL)
		return ;
	ptr = tokens;
	while (ptr && ft_strcmp(ptr->content, "|") != 0)
	{
		if (ft_strcmp(ptr->content, ">") == 0)
			ptr = set_mode(ptr, &(parsed->redirect_output), info, 0);
		else if (ft_strcmp((char *)ptr->content, "<") == 0)
			ptr = set_mode(ptr, &(parsed->redirect_input), info, 0);
		else if (ft_strcmp((char *)ptr->content, ">>") == 0)
			ptr = set_mode(ptr, &(parsed->redirect_output), info, APPEND);
		else if (ft_strcmp((char *)ptr->content, "<<") == 0)
			ptr = set_mode(ptr, &(parsed->here_docs), info, 0);
		else
			ptr = ptr->next;
	}
}

t_list *set_mode(t_list *tokens, t_list **add, t_info *info, int flag)
{
	t_list	*tmp;
	t_list	*node;
	char	*name;

	if (tokens->next == NULL)
		return (unexpected_token(NULL), NULL);
	else if (ft_isspecial(*tokens->next->content) == TRUE)
		return (unexpected_token(tokens->next->content), NULL);
	name = ft_strdup(tokens->next->content);
	if (name == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	node = lst_newvar_node(NULL, name, flag);
	if (node == NULL)
	{
		free(name);
		exit_error(info, __FILE__, __LINE__, "malloc");
	}
	ft_lstadd_back(add, node);
	tmp = tokens->next->next;
	ft_lstrmone(&info->token_lst, tokens->next, free);
	ft_lstrmone(&info->token_lst, tokens, free);
	return (tmp);
}

int add_args(t_list *node, t_info *info)
{
	t_list		*args;

	args = info->token_lst;
	if (args != NULL)
	{
		lst_get_parsed(node)->cmd = ft_strdup(args->content);
		if (lst_get_parsed(node)->cmd == NULL)
			exit_error(info, __FILE__, __LINE__, "malloc");
	}
	while (args && ft_strcmp(args->content, "|") != 0)
	{
		if (*(args->content) != 0)
			if (str_arr_add(&(lst_get_parsed(node)->args),
							args->content) == NULL)
				exit_error(info, __FILE__, __LINE__, "malloc");
		args = args->next;
	}
	return (SUCCESS);
}
