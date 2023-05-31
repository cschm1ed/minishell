/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:53:39 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/31 17:53:35 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirects(t_list *tokens, t_parsed *parsed, t_info *info)
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

t_list	*set_mode(t_list *tokens, t_list **add, t_info *info, int flag)
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

int	add_args(t_list *node, t_info *info, t_list *start)
{
	t_list		*args;

	args = start;
	if (args != NULL)
	{
		lst_get_parsed(node)->cmd = ft_strdup(args->content);
		if (lst_get_parsed(node)->cmd == NULL)
			exit_error(info, __FILE__, __LINE__, "malloc");
	}
	while (args && ft_strcmp(args->content, "|") != 0)
	{
		if (str_arr_add(&(lst_get_parsed(node)->args),
				args->content) == NULL)
			exit_error(info, __FILE__, __LINE__, "malloc");
		args = args->next;
	}
	return (SUCCESS);
}

int	invalid_colon(char *cmd)
{
	int	i;
	int	colon;

	colon = 0;
	i = 0;
	while (cmd[i] && (ft_isspace(cmd[i]) || cmd[i] == ':'))
	{
		if (cmd[i] == ':')
			colon++;
		i++;
	}
	if (!cmd[i] && colon == 1)
		return (g_exit_code = 0, TRUE);
	return (FALSE);
}

int	invalid_special(char *cmd)
{
	int	i;
	int	special;

	special = 0;
	i = 0;
	while (cmd[i]
		&& (ft_isspace(cmd[i]) || ft_isspecial(cmd[i]) || cmd[i] == '!'))
	{
		if (ft_isspecial(cmd[i]) || cmd[i] == '!')
			special++;
		i++;
	}
	if (!cmd[i] && special >= 1)
		return (g_exit_code = 258, unexpected_token("newline"), TRUE);
	return (FALSE);
}
