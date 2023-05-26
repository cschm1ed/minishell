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

// redirections
int		redirects(t_list **tokens, t_parsed *parsed, t_info *info);
int		delimiter_and_append(t_list **tokens, t_parsed *parsed, t_info *info);

#endif
