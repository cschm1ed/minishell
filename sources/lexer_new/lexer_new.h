/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_new.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:46:23 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/04 20:30:43 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef LEXER_NEW_H
# define LEXER_NEW_H

int		check_validity(char *str);
char	*remove_unnessecary(char *str);
t_list	*lexer_new(char *str);

#endif
