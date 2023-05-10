/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_replace_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:34:18 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/08 13:34:18 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int  get_name_len(const char *str);
static char *rejoin(char *str, char *value, int j, int len);
static char *replace_var(char *str, int *j, t_info *info);
static char *process_string(int *j, char **lexed, int i, t_info *info);

/**
 * @brief Replace variables in the given lexed array.
 *
 * @param info A pointer to the t_info structure containing variable values.
 * @param lexed The lexed strings array.
 * @return int SUCCESS if all variables are replaced successfully, FAILURE otherwise.
 */
int replace_variables(t_info *info, char **lexed)
{
	int i;
	int j;

	i = 0;
	while (lexed[i])
	{
		j = 0;
		while (lexed[i][j])
		{
			lexed[i] = process_string(&j, lexed, i, info);
			if (lexed[i] == NULL)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Process the lexed string and replace variables if necessary.
 *
 * @param j A pointer to the index of the current character in the lexed string.
 * @param lexed The lexed strings array.
 * @param i The index of the current lexed string.
 * @param info A pointer to the t_info structure containing variable values.
 * @return char* The processed string with variables replaced if necessary.
 */
static char *process_string(int *j, char **lexed, int i, t_info *info)
{
	char    *str;

	str = lexed[i];
	if (str[*j] == '$')
		return (replace_var(str, j, info));
	else if (str[*j] == '\'')
		skip_until_quote(str, (size_t *)j);
	else if (str[*j] == '"')
	{
		(*j)++;
		while (str[*j] && str[*j] != '"' && str[*j] != '$')
			(*j)++;
		if (str[*j] == '$')
			return (replace_var(str, j, info));
	}
	else
		(*j)++;
	return str;
}

/**
 * @brief Replace a variable in the input string.
 *
 * @param str The input string containing the variable.
 * @param j A pointer to the index of the variable in the input string.
 * @param info A pointer to the t_info structure containing variable values.
 * @return char* The string with the replaced variable value.
 */
static char *replace_var(char *str, int *j, t_info *info)
{
	char    *name;
	char    *ret;

	name = ft_substr(str, *j + 1, get_name_len(str + (*j)));
	ret = rejoin(str, find_var_val(info, name), *j, get_name_len(str + *j));
	*j += (int)ft_strlen(find_var_val(info, name));
	return (ret);
}

/**
 * @brief Create a new string with a replaced variable value.
 *
 * @param str The original string containing the variable.
 * @param value The variable value to be inserted.
 * @param j The index of the variable in the original string.
 * @param len The length of the variable name.
 * @return char* The new string with the replaced variable value.
 */
static char *rejoin(char *str, char *value, int j, int len)
{
	char    *ret;
	char    *s1;
	char    *s2;
	char    *s3;

	if (*str != '$')
	{
		s1 = ft_substr(str, 0, j);
		if (s1 == NULL)
			return (NULL);
	}
	else
		s1 = ft_strdup("");
	s2 = ft_strdup(value);
	if (s2 == NULL)
		return (free(s1), NULL);
	if (*(str + j + len) == 0)
		s3 = ft_strdup("");
	else
		s3 = ft_substr(str, j + len + 1, ft_strlen(str + j + len));
	if (s3 == NULL)
		return (free(s1), free(s2), NULL);
	ret = ft_strsjoin(s1, s2, s3);
	free(s1);
	free(s2);
	free(s3);
	free(str);
	return (ret);
}

/**
 * @brief Get the length of a variable name in a string.
 *
 * @param str The input string containing the variable name.
 * @return int The length of the variable name.
 */
static int  get_name_len(const char *str)
{
	int i;

	i = 0;
	if (*str == '$')
		str++;
	while (str && str[i] && (ft_isalnum(str[i]) == TRUE || str[i] == '_'))
		i++;
	return (i);
}
