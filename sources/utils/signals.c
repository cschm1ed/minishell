/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:13:51 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/31 17:53:14 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	keybindings_parent(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 1;
	}
	else if (signum == SIGQUIT)
		(void)signum;
}

void	keybindings_child(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_code = 130;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		g_exit_code = 131;
	}
}

void	setup_signals(void (*func)(int))
{
	signal (SIGINT, func);
	signal (SIGQUIT, func);
}
