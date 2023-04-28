/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:55:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/04/28 21:53:26 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    execute_echo(void)
{
	char    *args[] = {"Hello", "World", "REihe", "Na", NULL};
    int     i;
    
    i = -1;
    while (args[++i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
    }
    printf("$\n");
}
