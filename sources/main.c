/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 22:01:15 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int main(int argc, char **argv, char **env)
// {
//     t_info      *info;

//     info = info_init(env);
//     if (info == NULL)
//       return (1);
//     while (1)
//     {
//         info->commands->raw = ft_readline("minishell: ");
//         info->commands->lexed = lexer(commands.raw);
//         // if (commands.lexed)
//         // {
// 		//     commands.parsed = parser(&commands.parsed, commands.lexed);
//         //     print_parsed(commands.parsed);
//         // }
// 		// if (!commands.parsed)
// 		// 	printf(RED"You Died!\n"ESC);
//     }
// }

int main(int argc, char **argv, char **envp)
{
	t_commands  commands;
	t_info		*info;
	// char *cmd = "echo";
	char *args[] = {"Hello", "World", "Kein", "$PATH", NULL};

	signal(SIGINT, handle_keybindings);
	signal(SIGQUIT, handle_keybindings);
	info = info_init(envp);
	info->commands = &commands;
	if (info == NULL)
		return (printf("info error\n"), 1);
	commands.parsed = parser(info, &commands.parsed, args);
	print_parsed(commands.parsed);
	(void)argc;
	(void)argv;
	return (0);
}
