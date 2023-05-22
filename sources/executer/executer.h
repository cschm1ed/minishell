/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:01:11 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 12:01:11 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <minishell.h>

// main
int 	execute(t_info *info, t_list *parsed);

// builtins
int     execute_builtin_if(t_info *info, t_list *parsed, t_data *pipex, int cnt);

// execute
int		ft_child_process(t_data *pipex, t_list *parsed, t_info *info, int cnt);

// utils
char 	*get_path(char *cmd, t_info *info);
int 	check_infiles(t_list *parsed);
int 	create_outfiles(t_list *parsed);
void    close_pipes(int **pipes);

#endif
