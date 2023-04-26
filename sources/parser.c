/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:33:16 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/25 13:41:04 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_special(char **str, int *i, t_commands *cmd_info)

/**
 * @brief 
 * 
 * @param lexed - str-array the lexer created from user input
 * @return t_parsed* - a structure in which the information from the use input
 * 					   will be stored
 * Iterates through the tokens the lexer created. 
 * If a special token (specified in check_special) is recognized it will be 
 * handled by an appropriate function.
 * The first non speial token is interpreted as the command, other tokens will be 
 * interpreted as arguments of the command.
 * The function will only read till a pipe operator and create one struct per
 * command.
 * @return - parser() returns a linked list of commands and their context.
 */

t_parsed	*parser(char **lexed)
{
	t_parsed	*parsed;
	int			first;
	int			i;

	i = 0;
	first = TRUE;
	while (lexed[i])
	{
		if (check_special(lexed, &i, parsed) == FAILURE)
		{
			if (first == TRUE)
				parsed->cmd = lexed[i];
			else
			{
				parsed->args = str_arr_add(&parsed->args, lexed[i]);
				if (parsed->args == NULL)
					return (NULL);
			}
		}
		i ++;
	}
}

/**
 * @check_special - checks if token is a special expression
 * @param str - token from lexed input
 * @param i - position of token
 * @param parsed - struct to safe information to
 * checks if token from the lexer is a special token
 * these include: delimiters, redirections and wildcards.
 * If the special token is in relation to another input argument, e.g a file
 * a redirection points to, check special will also manage that input, and
 * adjust i accordingly.
 * @return int 
 */

static int	check_special(char **str, int *i, t_parsed *info)
{
	if (str[*i] == '>' && str[*i+1] != '>')
	{
		*i++;
		info->redirect_output = str[*i];
		return (SUCCESS);
	}
	else if (str[*i] == '<' && str[*i+1] != '<')
	{
		*i++;
		info->redirect_input = str[*i];
		return (SUCCESS);
	}
	else if (str[*i] == '>' && str[*i+1] == '>')
	{
		info->append_mode = TRUE;
		return (SUCCESS);
	}
	else if (str[*i] == '<' && str[*i+1] == '<')
	{
		*i++;
		info->delimiter = str[*i];
		return (SUCCESS);
	}
	return (FAILURE);
}

