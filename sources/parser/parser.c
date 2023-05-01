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

static int	check_special(char **str, int *i, t_parsed *cmd_info);

/**
 * @brief 
 * 
 * @param lexed - str-array the lexer created from user input
 * @return t_parsed* - a structure in which the information from the use
 * 									input will be stored
 * Iterates through the tokens the lexer created. 
 * If a special token (specified in check_special) is recognized it will be 
 * handled by an appropriate function.
 * The first non special token is interpreted as the command,
 * other tokens will be interpreted as arguments of the command.
 * The function will only read till a pipe operator or semicolon and create
 * one struct per command.
 * @return - parser() returns a linked list of commands and their context.
 */
t_parsed *parser(t_info *info, t_parsed **parsed, char **lexed)
{
	int			first;
	int			i;

	i = 0;
	first = TRUE;
	*parsed = ft_calloc(sizeof(t_parsed), 1);
	if (!*parsed)
		return (perror("malloc"), NULL);
	while (lexed[i])
	{
		if (check_special(lexed, &i, *parsed) == FAILURE)
		{
			if (lexed[i][0] == '|' || lexed[i][0] == ';')
			{
				if (parser(info, &((*parsed)->next), &lexed[i + 1]) == NULL)
					return (NULL);
				return (*parsed);
			}
			else if (first == TRUE) {
				(*parsed)->cmd = lexed[i];
				first = FALSE;
			}
			else
			{
				(*parsed)->args = str_arr_add((*parsed)->args, lexed[i]);
				if ((*parsed)->args == NULL)
					return (NULL);
			}
		}
		i ++;
	}
	return (*parsed);
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
	if (ft_strncmp(str[*i], ">", 2) == 0)
	{
		*i += 1;
		info->redirect_output = str[*i];
		return (SUCCESS);
	}
	else if (ft_strncmp(str[*i], "<", 2) == 0)
	{
		*i += 1;
		info->redirect_input = str[*i];
		return (SUCCESS);
	}
	else if (ft_strncmp(str[*i], ">>", 3) == 0)
	{
		info->append_mode = TRUE;
		return (SUCCESS);
	}
	else if (ft_strncmp(str[*i], "=", 2) == 0)
	{
		(void)i;
	}
	else if (ft_strncmp(str[*i], "<<", 3) == 0)
	{
		*i += 1;
		info->delimiter = str[*i];
		return (SUCCESS);
	}
	return (FAILURE);
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
