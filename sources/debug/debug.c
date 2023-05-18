/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:37:03 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 13:37:29 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_parsed(t_list *parsed)
{
	int	i;
	int	j;
	t_parsed	*content;
	i = 0;

	if (parsed == NULL)
		printf("parsed does not exist\n");
	while (parsed)
	{
		content = lst_get_parsed(parsed);
		printf(YELLOW"Node %d:\n"ESC, i);
		printf(GREEN"cmd:\t%s\n"ESC, content->cmd);
		j = 0;
		if (content->args)
		{
			printf(GREEN"args:"ESC);
			while (content->args[j])
			{
				printf(GREEN"\t%s, "ESC, content->args[j]);
				j ++;
			}
		}
		printf("\n");
		if (ft_lstlast(content->redirect_input) != NULL)
			printf(GREEN"last redirect input:\t%s\n"ESC,
				lst_get_var(ft_lstlast(content->redirect_input))->value);
		else
		printf(GREEN"no input redirection\n"ESC);
		if (ft_lstlast(content->redirect_output) != NULL)
			printf(GREEN"last redirect output:\t%s\n"ESC,
				lst_get_var(ft_lstlast(content->redirect_output))->value);
		else
		printf(GREEN"no output redirection\n"ESC);
		parsed = parsed->next;
		i ++;
	}
}

void	print_linked_lst(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char*)lst->content);
		lst = lst->next;
	}
}

void	print_lexed(char **array)
{
	int i;

	i = -1;
	while (array[++i])
		ft_printf(CYAN"%s\n"ESC, array[i]);
}
