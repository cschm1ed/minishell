/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:30:23 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/29 12:28:18 by lspohle          ###   ########.fr       */
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
t_list		*lst_newvar_node(char *name, char *value, int key);
char		*lsts_find_var_val(t_info *info, char *name);
int			lst_replace_var_val(t_list *list, char *name, char *new);

// str_arr_utils
int			str_in_arr(char **arr, char *find);
t_list		*str_arr_to_lst(char **arr);
char		**str_arr_add(char ***array, char *toadd);
void		bubble_sort_str_array(char **array, int len);
char **env_to_arr(t_info *info);

// frees and deletes
void		delete_variable(void *content);
void		delete_parsed(void *content);
void		free_pipex(t_data **pipex);
void		free_info(t_info **info);
void		free_cmds(t_commands *commands, t_info *info);
void		exit_error(t_info *info, char *file, int line, char *msg);
void		close_pipes(t_data **pipex);
// etc
t_info		*info_init(char **env);
int			unexpected_token(char *token);
char		*ft_readline(const char *str, t_info *info);
void		keybindings_parent(int signum);
void		keybindings_child(int signum);
void		rl_replace_line(char *c, int i);
void		setup_signals_parent(void);
void		setup_signals_child(void);

#endif
