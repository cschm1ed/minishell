/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:52:03 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/24 15:27:56 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <minishell.h>

// cd
int		execute_cd(t_info *info, char *directory);

// echo
int		execute_echo(t_parsed *parsed, int fd_out);

// env
int		execute_env(t_info *info, int fd_out);

// exit
int		execute_exit(t_info *info, char **arg, int exit_code);

// export
int		execute_export(t_info *info, char **arg, int fd_out);
int		print_sorted_lst(t_info *info, int fd_out);
char	**cpy_lst_to_array(t_list *lst, char ***array);
int		check_if_varname_is_valid(char *str);
int		var_lst_add(t_list **list, char **arg);

// pwd
int		execute_pwd(t_info *info, int fd_out);

// unset
int execute_unset(t_info *info, char **arg, int fd_out);

#endif
