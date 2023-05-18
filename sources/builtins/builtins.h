/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:52:03 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 11:52:03 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <minishell.h>

// cd
int			execute_cd(t_info *info, char *directory);

// echo
int			execute_echo(t_info *info, t_parsed *parsed);

// env
int execute_env(t_info *info);

// exit
int execute_exit(t_info *info, char **arg);

// export
int		execute_export(t_info *info, char **arg);
int		print_sorted_lst(t_info *info);
char	**cpy_lst_to_array(t_list *lst);
void	bubble_sort_str_array(char **array, int len);
int		check_if_varname_is_valid(char *str);
int		var_lst_add(t_list **list, char **arg);

// pwd
int		execute_pwd(t_info *info);

// unset
int		execute_unset(t_info *info, char **arg);

#endif
