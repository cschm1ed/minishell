/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 14:07:23 by lspohle          ###   ########.fr       */
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
		return (printf("info error\n"), 1);
	if (argc >= 3)
	{
		if (ft_strcmp(argv[2], "-n") == 0)
		{
			commands.raw = argv[3];
			commands.lexed = lexer(commands.raw, info);
			if (commands.lexed == NULL)
				return (1);
			if  (parser(&(commands.parsed), commands.lexed) == NULL)
				return (1);
			if (execute(info, commands.parsed) == FAILURE)
				return (1);
			return (0);
		}
	}
    while (1)
    {
        commands.raw = ft_readline("minishell: ");
        commands.lexed = lexer(commands.raw, info);
        if (commands.lexed)
        {
			// print_lexed(commands.lexed);
			// printf(RED"PWD: %s\n"ESC, info->pwd);
		    commands.parsed = parser(&commands.parsed, commands.lexed);
			execute(info, commands.parsed);
			// ft_free_dbl_ptr(commands.lexed);
        }
		// printf(RED"Exit: %d\n"ESC, info->exit_code);
		free(commands.raw);
    }
	(void)argc;
	(void)argv;
}
