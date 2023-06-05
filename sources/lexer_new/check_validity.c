/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:43:10 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/04 20:29:30 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_validity(char *str)
{
	if (valid_num_of_quotes(str) == FALSE)
	{
		ft_printf("minishell: syntax error: invalid num of quotes\n", STDERR_FILENO)
		return (FAILURE);
	}
	if (only_isspace(str) == FALSE)
		return (FAILURE);
}
