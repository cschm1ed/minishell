/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:15:23 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/30 15:26:11 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <minishell.h>

// main
char	**lexer(char *cmd, t_info *info);

// checks
int		valid_num_of_quotes(char *cmd);
int		valid_num_of_specials(char **lxd);

// replace vars
int		replace_variables(t_info *info, char **lexed);

// split
int		count_substrs(char *s);
char	**split_if_isspace_or_isspecial(char **split, char *s, int amt_substrs);

// trim
char	*trim_quotes(char *str);

// utils
int		skip_until_quote(const char *s, int *i);
int		skip_specials(char *s, int *i);

#endif
