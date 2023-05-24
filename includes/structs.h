/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:10:58 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/23 16:14:34 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_parsed		t_parsed;
typedef struct s_commands	t_commands;
typedef struct s_history	t_history;
typedef struct s_variable	t_variable;
typedef struct s_info		t_info;
typedef struct s_list		t_list;
typedef struct s_data		t_data;

typedef struct s_info {
	t_list		*env_lst;
	char		**env;
	t_list		*user_vars;
	t_list		*export_lst;
	t_commands	*commands;
	t_data		*pipex;
	char		*pwd;
}	t_info;

typedef struct s_parsed
{
	char	*cmd;
	char	**args;
	t_list	*redirect_input;
	t_list	*redirect_output;
	t_list	*here_docs;
}	t_parsed;

typedef struct s_variable
{
	int			key;
	char		*name;
	char		*value;
}	t_variable;

typedef struct s_commands
{
	char		*raw;
	char		**lexed;
	t_list		*parsed;
}	t_commands;

typedef struct s_history
{
	char		*cmd;
	t_history	*next;
}	t_history;

typedef struct s_data
{
	int		**pipe_fd;
	int		file_fd[2];
	pid_t	*pid;
	char	*cmd_path;
}	t_data;

#endif
