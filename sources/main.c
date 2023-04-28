/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/26 15:14:31 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
    t_commands  commands;
	t_info      info;

	if (info_init(env) == NULL)
		return (1);
    while (1)
    {
        commands.raw = ft_readline("minishell: ");
        commands.lexed = lexer(commands.raw);
        if (commands.lexed == NULL)
             ft_free_dbl_ptr(commands.lexed);
		 commands.parsed = parser(&commands.parsed, commands.lexed);
		 if (!commands.parsed)
			 return (printf("You Died!\n"), 1);
        print_parsed(commands.parsed);
    }
}
