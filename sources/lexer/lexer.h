/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:15:23 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/07 16:49:02 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <minishell.h>

// lexer.c
char	**lexer(char *cmd, t_info *info);

// lexer_checks.c
int		ft_isempty(char *cmd);
int		valid_num_of_quotes(char *cmd);
int		valid_num_of_specials(char **lxd);

// lexer_replace_vars.c
int		replace_variables(t_info *info, char **lexed);

// lexer_split.c
int		count_substrs(char *s);
char	**split_cmd(char **split, char *s, int amt_substrs);

// lexer_trim.c
char	*trim_quotes(char *str);

// lexer_utils.c
int		skip_until_quote(char *s, int *i);
int		skip_specials(char *s, int *i);

#endif
