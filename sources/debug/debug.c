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
		ft_printf("parsed does not exist\n");
	while (parsed)
	{
		content = lst_get_parsed(parsed);
		ft_printf(YELLOW"Node %d:\n"ESCAPE, i);
		ft_printf(GREEN"cmd:\t%s\n"ESCAPE, content->cmd);
		j = 0;
		if (content->args)
		{
			ft_printf(GREEN"args:"ESCAPE);
			while (content->args[j])
			{
				ft_printf(GREEN"\t%s, "ESCAPE, content->args[j]);
				j ++;
			}
		}
		ft_printf("\n");
		if (ft_lstlast(content->redirect_input) != NULL)
			ft_printf(GREEN"last redirect input:\t%s\n"ESCAPE,
				lst_get_var(ft_lstlast(content->redirect_input))->value);
		else
		ft_printf(GREEN"no input redirection\n"ESCAPE);
		if (ft_lstlast(content->redirect_output) != NULL)
			ft_printf(GREEN"last redirect output:\t%s\n"ESCAPE,
				lst_get_var(ft_lstlast(content->redirect_output))->value);
		else
		ft_printf(GREEN"no output redirection\n"ESCAPE);
		parsed = parsed->next;
		i ++;
	}
}

void	print_linked_lst(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", (char*)lst->content);
		lst = lst->next;
	}
}
