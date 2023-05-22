/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:37:07 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/22 14:37:07 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    exit_error(t_info *info, char *file, int line, char *msg)
{
	if (file)
		ft_printf("%s: ", file);
	if (line)
		ft_printf("c (%d): ", line);
	if (msg)
		perror(msg);
	execute_exit(info, NULL, 1);
}
