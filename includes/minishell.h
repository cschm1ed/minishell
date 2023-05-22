/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:04:45 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/22 15:28:26 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define SYNERR "minishell: syntax error\n"
# define SUCCESS 1
# define FAILURE 0
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
