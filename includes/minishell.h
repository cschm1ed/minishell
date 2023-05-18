/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:04:45 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/13 17:06:39 by lspohle          ###   ########.fr       */
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

// inits
t_info		*info_init(char **env);

// utils
char		*ft_readline(const char *str);
int			ft_isspace(char c);
int			ft_isquote(char c);
int			ft_isspecial(char c);
int			ft_isredirect(char c);
char		**str_arr_add(char ***arr, char *toadd);
void		ft_lstrmone(t_list **head, t_list *node, void (*del)(void*));
void		delete_variable(void *content);
int			var_lst_add(t_list **list, char **arg);
t_variable	*lst_get_var(t_list *lst);
int			ft_strcmp(const char *str1, const char *str2);
char		*lst_find_var_val(t_list *lst, char *name);
char		*find_var_val(t_info *info, char *name);
int			str_in_arr(char **arr, char *find);
t_list		*str_arr_to_lst(char **arr);
void		delete_parsed(void *content);
t_parsed	*lst_get_parsed(t_list *lst);
t_list		*lst_newparsed_node();
int			unexpected_token(char *token);
char		*ft_strsjoin(const char *s1, const char *s2, const char *s3);
t_list  	*lst_find_node(t_list *lst, char *name);
t_list *lst_newvar_node(char *name, char *value, int key);

// signals
void		handle_keybindings(int signum);

// tests
void		print_parsed(t_list *parsed);
int			test_parser(void);
void		print_lexed(char **array);
void		print_linked_lst(t_list *lst);

#endif
