/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/26 11:08:50 by cschmied         ###   ########.fr       */
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
             printf("Keep going!\n");
		 commands.parsed = parser(&commands.parsed, commands.lexed);
		 if (!commands.parsed)
			 return (printf("You Died!\n"), 1);
     }
}
