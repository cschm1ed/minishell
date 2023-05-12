/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:55:00 by lspohle           #+#    #+#             */
/*   Updated: 2023/05/12 12:10:18 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_args(char **args, int j)
{
	while (args[j])
	{
		printf("%s", args[j]);
		if (args[++j])
			printf(" ");
	}
}

static int	ft_isoption(char *args)
{
	int	i;

	i = -1;
	if (args[++i] == '-')
	{
		while (args[++i])
			if (args[i] != 'n')
				return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

int execute_echo(t_info *info, t_parsed *parsed)
{
	char	**args;
	int		j;
	
	args = parsed->args;
	j = 0;
	if (ft_isoption(args[j]))
		while (args[++j])
			if (!ft_isoption(args[j]))
				break;
	print_args(args, j);
	if (!ft_isoption(args[0]))
		printf("\n");
	return (info->exit_code = 0, SUCCESS);
}
