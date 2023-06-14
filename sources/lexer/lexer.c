/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:03:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/06/14 10:44:47 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**check_and_trim_quotes(char **lexed);
static int	preserve_as_literal(t_info *info, char **lexed, int substrs);

/**
 * @brief splits the input into an array of strings and handles syntax errors
 * 
 * @param cmd - the user's input
 * @param info - struct with neccessary info (environmental variables, etc)
 * @return char** - splitted command into a two dimensional array
 */
char	**lexer(char *cmd, t_info *info)
{
	char	**lexed;
	int		substrs;

	if (cmd == NULL || *cmd == 0
		|| valid_num_of_quotes(cmd) == FALSE || ft_isempty(cmd) == TRUE)
		return (NULL);
	substrs = count_substrs(cmd);
	lexed = ft_calloc(substrs + 1, sizeof(char *));
	if (!lexed)
		return (perror("malloc"), NULL);
	lexed = split_cmd(lexed, cmd, substrs);
	if (!lexed)
		return (NULL);
	if (preserve_as_literal(info, lexed, substrs) == FAILURE
		|| replace_variables(info, lexed) == FAILURE)
		return (NULL);
	lexed = check_and_trim_quotes(lexed);
	if (valid_num_of_specials(lexed) == FALSE)
		return (ft_free_dbl_ptr(&lexed));
	return (lexed);
}

/**
 * @brief prevents the shell from interpreting metacharacters within quotes
 * (except for dollar sign)
 * 
 * @param info - struct with neccessary info (flag to preserve_literal)
 * @param lexed - splitted command into a two dimensional array
 * @param substrs - amount of substrs from the command
 * @return int - status whether allocation succeeded or failed
 */
static int	preserve_as_literal(t_info *info, char **lexed, int substrs)
{
	int	i;
	int	j;

	info->preserve_literal = ft_calloc(sizeof(int), substrs);
	if (info->preserve_literal == NULL)
		return (perror("malloc"), FAILURE);
	i = -1;
	while (lexed[++i])
	{
		j = -1;
		while (lexed[i][++j])
			if (ft_isquote(lexed[i][j]) == TRUE)
				info->preserve_literal[i] = TRUE;
	}
	return (SUCCESS);
}

/**
 * @brief checks the quotation marks and trims them appropriately
 * 
 * @param lexed - splitted command into a two dimensional array
 * @return char** - trimmed two dimensional array
 */
static char	**check_and_trim_quotes(char **lexed)
{
	char	*trimmed;
	int		i;

	i = -1;
	while (lexed[++i])
	{
		if (valid_num_of_quotes(lexed[i]) == FALSE)
			return (NULL);
		trimmed = trim_quotes(ft_strdup(lexed[i]));
		if (!trimmed)
			return (free (trimmed), ft_free_dbl_ptr(&lexed));
		free (lexed[i]);
		lexed[i] = trimmed;
	}
	if (ft_strlen(lexed[0]) == 0)
		ft_printf("minishell: %s: command not found\n", STDERR_FILENO, lexed[0]);
	return (lexed);
}
