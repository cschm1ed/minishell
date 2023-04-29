/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:42:12 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 17:27:51 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	str_isspace(char *str);

/**
 * @brief - ft_readline reads one line from stdin and adds it to history
 * @param str - message to be displayed, when awaiting input
 * reads one line from stdin and adds it to history if it contains non
 * whitespace characters.
 * @return char* - returns the line read
 */

char	*ft_readline(const char *str)
{
	char *tmp;

	tmp = readline(str);
	if (tmp && !str_isspace(tmp))
		add_history(tmp);
	return (tmp);
}

static int	str_isspace(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (SUCCESS);
	while (str[++i])
		if (!ft_isspace(str[i]))
			return (FALSE);
	return (TRUE);
}

void	handle_keybindings(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
	}
	else if (signum == SIGQUIT)
		ft_printf("ctrl+ backslash");
}
