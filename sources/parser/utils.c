/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:43:10 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/04 15:43:10 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_parsed(t_list *parsed)
{
	int	i;
	int	j;

	i = 0;
	if (parsed == NULL)
		printf("parsed does not exist\n");
	while (parsed)
	{
		printf(YELLOW"Node %d:\n"ESC, i);
		printf(GREEN"cmd:\t%s\n"ESC, lst_get_parsed(parsed)->cmd);
		j = 0;
		if (lst_get_parsed(parsed)->args)
		{
			printf(GREEN"args:"ESC);
			while (lst_get_parsed(parsed)->args[j])
			{
				printf(GREEN"\t%s, "ESC, lst_get_parsed(parsed)->args[j]);
				j ++;
			}
		}
		printf("\n");
		printf(GREEN"redirect input:\t%s\n"ESC,
			   ft_lstlast(lst_get_parsed(parsed)->redirect_input)->content);
		printf(GREEN"redirect output:\t%s\n"ESC,
			   ft_lstlast(lst_get_parsed(parsed)->redirect_output)->content);
		printf(GREEN"delimiter:\t%s\n"ESC,
			   lst_get_parsed(parsed)->delimiter);
		printf(GREEN"append mode:\t%d\n\n"ESC,
			   lst_get_parsed(parsed)->append_mode);
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
