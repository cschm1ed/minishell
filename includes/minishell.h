/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:56 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/24 18:04:54 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 1
# define FAILURE 0
# define TRUE 1
# define FALSE 0

typedef struct s_parsed
{
    char    *cmd;
    char    **args;
    char    *redirect_input:
    char    *redirect_outpu;
    char    *delimiter;
    int     append_mode;
}   t_parsed;

typedef struct s_commands
{
    char        *raw;
    char        **lexed;
    t_parsed    *parsed;
}   t_commands;

typedef struct s_history
{
    char        *cmd;
    t_history   *next;
}   t_history;

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

char	**lexer(char *cmd);

#endif

