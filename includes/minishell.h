/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:38:56 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/26 14:51:33 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 1
# define FAILURE 0
# define TRUE 1
# define FALSE 0

typedef struct s_parsed t_parsed;
typedef struct s_commands t_commands;
typedef struct s_history t_history;

typedef struct s_parsed
{
    char        *cmd;
    char        **args;
    char        *redirect_input;
    char        *redirect_output;
    char        *delimiter;
    int         append_mode;
    t_parsed    *next;
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
char    *ft_readline(const char *str);

// utils
int 	ft_isspace(char c);
char	**str_arr_add(char ***arr, char *toadd);

#endif

