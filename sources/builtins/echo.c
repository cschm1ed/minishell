/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:55:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/03 19:00:47 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_echo(t_parsed *parsed)
{
	int	i;
	
	i = -1;
	if (!ft_strncmp(parsed->args[0], "-n", 3))
		i++;
	while (parsed->args[++i])
	{
		printf("%s", parsed->args[i]);
		if (parsed->args[i + 1])
			printf(" ");
	}
	if (ft_strncmp(parsed->args[0], "-n", 3))
		printf("\n");
}
