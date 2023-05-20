/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:30:23 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 12:30:23 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <minishell.h>

// lst_utils
void		ft_lstrmone(t_list **head, t_list *node, void (*del)(void*));
char		*lst_find_var_val(t_list *lst, char *name);
t_list		*lst_find_node(t_list *lst, char *name);
t_variable	*lst_get_var(t_list *lst);
t_parsed	*lst_get_parsed(t_list *lst);
t_list		*lst_newparsed_node(void);
t_list 		*lst_newvar_node(char *name, char *value, int key);
char		*lsts_find_var_val(t_info *info, char *name);
int 		lst_replace_var_val(t_list *list, char *name, char *new);

// str_arr_utils
int			str_in_arr(char **arr, char *find);
t_list		*str_arr_to_lst(char **arr);
char		**str_arr_add(char ***array, char *toadd);

// frees and deletes
void		delete_variable(void *content);
void		delete_parsed(void *content);

// etc
t_info		*info_init(char **env);
int			unexpected_token(char *token);
char		*ft_readline(const char *str, t_info *info);
void		handle_keybindings(int signum);

#endif
