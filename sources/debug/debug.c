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
		printf(YELLOW"Node %d:\n"ESCAPE, i);
		printf(GREEN"cmd:\t%s\n"ESCAPE, content->cmd);
		j = 0;
		if (content->args)
		{
			printf(GREEN"args:"ESCAPE);
			while (content->args[j])
			{
				printf(GREEN"\t%s, "ESCAPE, content->args[j]);
				j ++;
			}
		}
		printf("\n");
		if (ft_lstlast(content->redirect_input) != NULL)
			printf(GREEN"last redirect input:\t%s\n"ESCAPE,
				lst_get_var(ft_lstlast(content->redirect_input))->value);
		else
		printf(GREEN"no input redirection\n"ESCAPE);
		if (ft_lstlast(content->redirect_output) != NULL)
			printf(GREEN"last redirect output:\t%s\n"ESCAPE,
				lst_get_var(ft_lstlast(content->redirect_output))->value);
		else
		printf(GREEN"no output redirection\n"ESCAPE);
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
		ft_printf(CYAN"%s\n"ESCAPE, array[i]);
}
