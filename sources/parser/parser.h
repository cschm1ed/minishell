/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:33 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/30 15:26:27 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// main
t_list	*parser(t_list **parsed, char **lexed, t_info *info);

// parser_utils
int		add_args(t_list *node, t_info *info, t_list *start);
void	redirects(t_list *tokens, t_parsed *parsed, t_info *info);
t_list	*set_mode(t_list *tokens, t_list **add, t_info *info, int flag);
int		invalid_colon(char *cmd);
int		invalid_special(char *cmd);
int     is_literal(t_list *node, t_info *info);


#endif
