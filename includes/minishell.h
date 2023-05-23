/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:04:45 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/23 16:23:05 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int	g_exit_code;

# define SYNERR "minishell: syntax error\n"
# define SUCCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0
# define APPEND 1
# define REDIRECT 0
# define DELIMITER 1

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "../libft/libft.h"
# include "colors.h"
# include "structs.h"

# include "../sources/builtins/builtins.h"
# include "../sources/executer/executer.h"
# include "../sources/lexer/lexer.h"
# include "../sources/parser/parser.h"
# include "../sources/utils/utils.h"
# include "../sources/debug/debug.h"

// void	rl_replace_line(char *c, int i);

#endif
