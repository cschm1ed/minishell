/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:20:33 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 12:20:33 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// main
t_list	*parser(t_list **parsed, char **lexed, t_info *info);

int		add_args(t_list *node, t_info *info, t_list *start);
void	redirects(t_list *tokens, t_parsed *parsed, t_info *info);
t_list	*set_mode(t_list *tokens, t_list **add, t_info *info, int flag);

#endif
