/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:04:45 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 21:11:34 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 1
# define FAILURE 0
# define TRUE 1
# define FALSE 0

# define SYNERR "minishell: syntax error\n"
# define PARERR "minishell: parse error\n"

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# include "colors.h"
# include "structs.h"

void rl_replace_line (const char *text, int clear_undo);

// inits
t_info		*info_init(char **env);

// parser
t_parsed	*parser(t_parsed **parsed, char **lexed);

// utils
char		*ft_readline(const char *str);
int			ft_isspace(char c);
int			ft_isquote(char c);
int			ft_isspecial(char c);
int			ft_isredirect(char c);
char		**str_arr_add(char **arr, char *toadd);
void		ft_lstrmone(t_list **head, t_list *node, void (*del)(void*));
void		delete_variable(void *content);
int			var_lst_add(t_list **list, char **arg);
t_variable	*lst_get_var(t_list *lst);

// signals
void		handle_keybindings(int signum);

// tests
void		print_parsed(t_parsed *parsed);
int			test_parser(void);

// lexer/lexer_checks.c
int			valid_num_of_quotes(char *s);
int			valid_quotes(char **substr);
int			valid_num_of_specials(char **substr);

// lexer/lexer_utils.c
int			count_substrs(char *s);
int			locate_substr(char *s, size_t *start, size_t *end);

// lexer/lexer.c
char		**lexer(char *cmd);

// bultins
void		execute_pwd(char **envp);
void		execute_echo(void);
void		builtin_env(t_info *info);
int			export(t_info *info, char **arg);

#endif
