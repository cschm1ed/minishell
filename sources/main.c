/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/26 19:47:20 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
    t_commands  commands;

    while (1)
    {
        commands.raw = ft_readline("minishell: ");
        commands.lexed = lexer(commands.raw);
        if (commands.lexed == NULL)
            ft_free_dbl_ptr(commands.lexed);
        else
        {
		    commands.parsed = parser(&commands.parsed, commands.lexed);
            print_parsed(commands.parsed);
        }
		if (!commands.parsed)
			printf(RED"You Died!\n"ESC);
    }
}
