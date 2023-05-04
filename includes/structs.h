/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:10:58 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/03 18:44:21 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_parsed		t_parsed;
typedef struct s_commands	t_commands;
typedef struct s_history	t_history;
typedef struct s_variable	t_variable;
typedef struct s_info		t_info;

typedef struct s_info
{
	t_list		*lex_lst;
	t_list		*env_lst;
	t_list		*user_vars;
	t_commands	*commands;
	int			exit_code;
	char 		*pwd;
}   t_info;

typedef struct s_parsed
{
	char		*cmd;
	char		**args;
	char		*redirect_input;
	char		*redirect_output;
	char 		*delimiter;
	int			append_mode;
	t_parsed	*next;
}	t_parsed;

typedef struct s_variable
{
	char		*name;
	char		*value;
}	t_variable;

typedef struct s_commands
{
	char		*raw;
	char		**lexed;
	t_list		*token_lst;
	t_parsed	*parsed;
}	t_commands;

typedef struct s_history
{
	char		*cmd;
	t_history	*next;
}	t_history;

#endif
