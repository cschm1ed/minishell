/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:43:10 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/04 16:43:10 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_validity(char *str)
{
	if (valid_num_of_quotes(str) == FALSE)
		return (FAILURE);
	if (only_isspace(str) == FALSE)
		return (FAILURE);
}
