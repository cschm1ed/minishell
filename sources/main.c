/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/29 18:09:34 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	command_line_mode(char *const *argv, t_commands *commands,
			t_info *info);

void	print_lexed(char **lxd)
{
	int i;

	i = 0;
	while (lxd[i])
		printf("%s\n", lxd[i++]);
	printf(RED"--end--\n"ESCAPE);
}

void	print_parsed(t_info *info)
{
	t_list		*ptr;
	t_parsed	*parsed;

	ptr = info->commands->parsed;
	while (ptr)
	{
		parsed = lst_get_parsed(ptr);
		printf("command: %s\n", parsed->cmd);
		if (lst_get_var(parsed->redirect_output))
			printf("out:	 %s\n", lst_get_var(parsed->redirect_output)->value);
		if (lst_get_parsed(parsed->redirect_input))
			printf("in:	 %s\n", lst_get_var(parsed->redirect_input)->value);
		printf("--end node--\n");
		ptr = ptr->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_commands	commands;
	t_info		*info;

	commands.raw = NULL;
	commands.lexed = NULL;
	commands.parsed = NULL;
	info = info_init(envp);
	if (info == NULL)
		return (perror("info"), 1);
	info->commands = &commands;
	if (info == NULL)
		return (ft_printf("info error\n"), 1);
	while (1)
	{
		commands.raw = ft_readline("minishell: ", info);
		commands.lexed = lexer(commands.raw, info);
		if (commands.lexed && commands.lexed[0])
		{
			commands.parsed = parser(&commands.parsed, commands.lexed, info);
			if (commands.parsed != NULL)
			{
				//printf("size: %d\n", ft_lstsize(commands.parsed));
				//print_parsed(info);
				execute(info, commands.parsed);
			}
		}
		free_cmds(&commands, info);
	}
	return ((void)argc, (void)argv, 0);
}
