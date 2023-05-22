/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/22 10:48:50 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int argc, char **argv, char **envp)
{
	t_commands  commands;
	t_info		*info;

	signal(SIGINT, handle_keybindings);
	signal(SIGQUIT, handle_keybindings);
	info = info_init(envp);
	if (info == NULL)
		return (perror("info"), 1);
	info->commands = &commands;
	if (info == NULL)
		return (ft_printf("info error\n"), 1);
	if (argc >= 3)
	{
		if (ft_strcmp(argv[1], "-n") == 0)
		{
			commands.raw = argv[2];
			commands.lexed = lexer(commands.raw, info);
			if (commands.lexed)
			{
				commands.parsed = parser(&commands.parsed, commands.lexed);
				if (commands.parsed == NULL)
					execute_exit(info, NULL, 1);
				execute(info, commands.parsed);
			}
			//free_cmds(&commands);
			return (0);
		}
	}
    while (1)
    {
        commands.raw = ft_readline("minishell: ", info);
		commands.lexed = lexer(commands.raw, info);
		if (commands.lexed)
        {
			print_lexed(commands.lexed);
			commands.parsed = parser(&commands.parsed, commands.lexed);
			if (commands.parsed == NULL)
				execute_exit(info, NULL, 1);
			execute(info, commands.parsed);
		}
	    free_cmds(&commands);
    }
	(void)argc;
	(void)argv;
}
