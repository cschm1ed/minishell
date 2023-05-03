/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:04:45 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/03 19:15:18 by lspohle          ###   ########.fr       */
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
t_parsed	*parser(t_info *info, t_parsed **parsed, char **lexed);
void		replace_variables(t_info *info, t_list *token_lst);
void		*find_and_remove_redirects(t_list *tokens, t_parsed *parsed);
void	*find_and_remove_delimiter_and_append(t_list *tokens, t_parsed *parsed);

// utils
char		*ft_readline(const char *str);
int			ft_isspace(char c);
int			ft_isquote(char c);
int			ft_isspecial(char c);
int     	ft_isvariable(char c, char next);
int			ft_isredirect(char c);
char		**str_arr_add(char **arr, char *toadd);
void		ft_lstrmone(t_list **head, t_list *node, void (*del)(void*));
void		delete_variable(void *content);
int			var_lst_add(t_list **list, char **arg);
t_variable	*lst_get_var(t_list *lst);
int			ft_strcmp(const char *str1, const char *str2);
char		*lst_find_var_val(t_list *lst, char *name);
int			str_in_arr(char **arr, char *find);
t_list		*str_arr_to_lst(char **arr);



// signals
void		handle_keybindings(int signum);

// tests
void		print_parsed(t_parsed *parsed);
int			test_parser(void);

// lexer/lexer_checks.c
int			valid_num_of_quotes(char *s, t_info *info);
int			valid_quotes(char **substr);
int			valid_num_of_specials(char **substr, t_info *info);

// lexer/lexer_utils.c
int			count_substrs(char *s);
int			locate_substr(char *s, size_t *start, size_t *end);

// lexer/lexer.c
char		**lexer(char *cmd, t_info *info);

// bultins
void		execute_pwd(t_info *info);
void	    execute_echo(t_parsed *parsed);
void		builtin_env(t_info *info);
void    	execute_exit(t_info *info);
int			export(t_info *info, char **arg);

// executer/executer.c
int			executer(t_info *info, t_commands commands);

#endif
