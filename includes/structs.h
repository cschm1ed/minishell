/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:10:58 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/07 15:57:41 by lspohle          ###   ########.fr       */
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
typedef struct s_executable	t_executable;

typedef struct s_info
{
	t_list					*env_lst;
	char					**env;
	t_list					*user_vars;
	t_list					*export_lst;
	t_list					*token_lst;
	int						*preserve_literal;
	t_commands				*commands;
	t_executable			*builtins;
	t_data					*pipex;
	char					*pwd;
	char					*home_path;
}							t_info;

typedef struct s_parsed
{
	int						hdoc;
	char					*cmd;
	char					**args;
	t_list					*redirect_input;
	t_list					*redirect_output;
	t_list					*here_docs;
	int						heredoc_pipe[2];
}							t_parsed;

typedef struct s_variable
{
	int						key;
	char					*name;
	char					*value;
}							t_variable;

typedef struct s_commands
{
	char					*raw;
	char					**lexed;
	t_list					*parsed;
}							t_commands;

typedef struct s_history
{
	char					*cmd;
	t_history				*next;
}							t_history;

typedef struct s_data
{
	pid_t					heredoc_pid;
	int						**pipe_fd;
	int						file_fd[2];
	pid_t					*pid;
	char					*cmd_path;
}							t_data;

typedef struct s_executable
{
	const char				*command;
	int						(*execute_function)(t_info *, char **, int);
}							t_executable;

#endif
