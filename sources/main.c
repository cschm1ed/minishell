/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/31 17:53:53 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	print_lexed(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		printf("%s\n", str[i++]);
// }

// void	print_parsed(t_list *parsed)
// {
// 	int	i;
// 	int	j;
// 	t_parsed	*content;
// 	i = 0;

// 	if (parsed == NULL)
// 		ft_printf("parsed does not exist\n");
// 	while (parsed)
// 	{
// 		content = lst_get_parsed(parsed);
// 		ft_printf(YELLOW"Node %d:\n"ESCAPE, i);
// 		ft_printf(GREEN"cmd:\t%s\n"ESCAPE, content->cmd);
// 		j = 0;
// 		if (content->args)
// 		{
// 			ft_printf(GREEN"args:"ESCAPE);
// 			while (content->args[j])
// 			{
// 				ft_printf(GREEN"\t%s, "ESCAPE, content->args[j]);
// 				j ++;
// 			}
// 		}
// 		ft_printf("\n");
// 		if (ft_lstlast(content->redirect_input) != NULL)
// 			ft_printf(GREEN"last redirect input:\t%s\n"ESCAPE,
// 				lst_get_var(ft_lstlast(content->redirect_input))->value);
// 		else
// 		ft_printf(GREEN"no input redirection\n"ESCAPE);
// 		if (ft_lstlast(content->redirect_output) != NULL)
// 			ft_printf(GREEN"last redirect output:\t%s\n"ESCAPE,
// 				lst_get_var(ft_lstlast(content->redirect_output))->value);
// 		else
// 		ft_printf(GREEN"no output redirection\n"ESCAPE);
// 		parsed = parsed->next;
// 		i ++;
// 	}
// }

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
				execute(info, commands.parsed);
		}
		free_cmds(&commands, info);
	}
	return ((void)argc, (void)argv, 0);
}
