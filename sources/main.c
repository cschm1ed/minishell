/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/03 17:57:21 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_commands  commands;
	t_info		*info;

	signal(SIGINT, handle_keybindings);
	signal(SIGQUIT, handle_keybindings);
	info = info_init(envp);
	if (!info)
		return (printf("info error\n"), 1);
	//export(info, NULL);
    while (1)
    {
        commands.raw = ft_readline("minishell: ");
        commands.lexed = lexer(commands.raw, info);
		printf(MAGENTA"Exit_code: %d\n"ESC, info->exit_code);
		//execute_echo();
		
        // if (commands.lexed)
        // {
		//     commands.parsed = parser(&commands.parsed, commands.lexed);
        //     print_parsed(commands.parsed);
        // }
		// if (ft_strncmp(commands.parsed->cmd, "pwd", 4) == 0)
		// {
		// 	execute_pwd(envp);
		// }
    }
}