/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:15:23 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 12:15:23 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <minishell.h>

// main
char	**lexer(char *cmd, t_info *info);

// checks
int		valid_num_of_quotes(char *cmd, t_info *info);
int		valid_num_of_specials(char **lxd, t_info *info);

// replace vars
int		replace_variables(t_info *info, char **lexed);

// split
int		count_substrs(char *s);
char	**split_if_isspace(char **split, char *s, int amt_substrs);

// trim
char	*trim_quotes(char *str);

// utils
int 	skip_until_quote(const char *s, size_t *i);
int		skip_specials(char *s, size_t *i);

#endif