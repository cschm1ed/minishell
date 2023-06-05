/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_unnecessary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:30:59 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/04 20:42:42 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <minishell.h>

char *remove_unnecessary(char *str)
{
	char	*out;
	int		i;

	out	= ft_calloc(sizeof(char), ft_strlen(str));
	if (out == NULL)
		return (perror("malloc"), NULL);
	while (str[i])
	{
		if (ft_isspace(str[i]))
			skip_spaces(str, &i);
		else if (str[i] == '\'')
			skip_singles(str, &i);
		out[i] == str[i];
	}
}
