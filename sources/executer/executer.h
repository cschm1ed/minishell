/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:01:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/14 12:13:06 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <minishell.h>

// main
int		execute(t_info *info, t_list *parsed);

// builtins
int		execute_builtin_if(t_info *info, t_list *parsed,
			t_data *pipex, int cnt);
int		execute_single(t_info *info, t_list *parsed, t_data *pipex);

// execute
int		ft_child_process(t_data *pipex, t_list *parsed, t_info *info, int cnt);

// heredoc
int		heredoc_redirect(t_list *parsed, t_data *pipex, t_info *info);

// path
char	*get_path(char *cmd, t_info *info);

// utils
int		check_infiles(t_list *parsed);
int		create_outfiles(t_list *parsed);
int		handle_files(t_data *pipex, t_list *parsed);

#endif
