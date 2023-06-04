/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:19:59 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/04 16:19:59 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define ESCAPEC 1
# define EXPANSION 2
# define PATH_EXPANSION 3
# define LITERAL 4
# define STR_LITERAL 5
# define OPERATOR 6
# define WORD 7

typedef enum
{
	ESCAPEC,
	EXPANSION,
	PATH_EXPANSION,
	LITERAL,
	STR_LITERAL,
	OPERATOR,
	WORD

}	t_type;

typedef struct s_token
{
	char	*content;
	char	*group;
	char	*next_group;
	t_type 	type;
}	t_token;

t_list	*lexer_new(char *str)
{
	t_token	*tokens;

	if (check_validity(str) == FAILURE)
		return (NULL);
	str = remove_unnessecary(str);
	if (str == NULL)
		return (NULL);
	tokens = tokenization(str);
	if (tokens == NULL)
		return (NULL);
	if (check_syntax(tokens) == NULL)
		return (NULL);
	return (tokens);
}
