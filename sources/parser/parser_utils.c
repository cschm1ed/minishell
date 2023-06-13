/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:53:39 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/07 15:55:06 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief iterates through command to find redirections
 * @param tokens
 * @param parsed
 * @param info
 */
void	redirects(t_list *tokens, t_parsed *parsed, t_info *info)
{
	t_list	*ptr;

	if (tokens == NULL)
		return ;
	ptr = tokens;
	while (ptr && (ft_strcmp(ptr->content, "|") != 0) && !is_literal(ptr, info))
	{
		if (!ft_strcmp(ptr->content, ">") && !is_literal(ptr, info))
			ptr = set_mode(ptr, &(parsed->redirect_output), info, 0);
		else if (!ft_strcmp((char *)ptr->content, "<") && !is_literal(ptr,
				info))
			ptr = set_mode(ptr, &(parsed->redirect_input), info, 0);
		else if (!(ft_strncmp(ptr->content, ">>", ft_strlen(ptr->content) + 1)
				&& !is_literal(ptr, info)))
			ptr = set_mode(ptr, &(parsed->redirect_output), info, APPEND);
		else if (!ft_strcmp((char *)ptr->content, "<<") && !is_literal(ptr,
				info))
			ptr = set_mode(ptr, &(parsed->here_docs), info, 0);
		else
			ptr = ptr->next;
	}
}

/**
 * @brief appends redirect arg to corresponding list
 * @param tokens
 * @param add
 * @param info
 * @param flag
 * @return next token to interpret
 */
t_list	*set_mode(t_list *tokens, t_list **add, t_info *info, int flag)
{
	t_list	*tmp;
	t_list	*node;
	char	*name;

	if (tokens->next == NULL)
		return (unexpected_token(NULL), NULL);
	else if (ft_isspecial(*tokens->next->content) == TRUE
		&& !is_literal(tokens->next, info))
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
	tokens->next->flag = TRUE;
	tokens->flag = TRUE;
	return (tmp);
}

/**
 * @brief finds command in remaining tokens and reads arguments
 * @param node
 * @param info
 * @param start
 * @return SUCCESS
 */
void	add_args(t_list *node, t_info *info, t_list *start)
{
	t_list	*args;

	args = start;
	while (args->flag)
		args = args->next;
	if (args != NULL)
	{
		lst_get_parsed(node)->cmd = ft_strdup(args->content);
		if (lst_get_parsed(node)->cmd == NULL)
			exit_error(info, __FILE__, __LINE__, "malloc");
	}
	while (args && args->flag != TRUE && !(ft_strcmp(args->content, "|") == 0
			&& !is_literal(args, info)))
	{
		if (str_arr_add(&(lst_get_parsed(node)->args), args->content) == NULL)
			exit_error(info, __FILE__, __LINE__, "malloc");
		args = args->next;
	}
}

/**
 * @brief checks for syntax errors in given token
 * @param cmd
 * @return TRUE or FALSE
 */
int	invalid_colon(char *cmd)
{
	int	i;
	int	colon;

	colon = 0;
	i = 0;
	while (cmd[i] && (ft_isspace(cmd[i]) || cmd[i] == ':'))
		if (cmd[i++] == ':')
			colon++;
	if (!cmd[i] && colon == 1)
		return (g_exit_code = 0, TRUE);
	return (FALSE);
}

/**
 * @brief checks for syntax errors in given token
 * @param cmd
 * @return TRUE or FALSE
 */
int	invalid_special(char *cmd)
{
	int	i;
	int	special;

	special = 0;
	i = 0;
	while (cmd[i] && (ft_isspace(cmd[i]) || ft_isspecial(cmd[i])
			|| cmd[i] == '!'))
	{
		if (ft_isspecial(cmd[i]) || cmd[i] == '!')
			special++;
		i++;
	}
	if (!cmd[i] && special >= 1)
		return (g_exit_code = 258, unexpected_token("newline"), TRUE);
	return (FALSE);
}
