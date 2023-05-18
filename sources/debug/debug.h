/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:36:51 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/18 13:36:51 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <minishell.h>

void	print_parsed(t_list *parsed);
void	print_linked_lst(t_list *lst);
void	print_lexed(char **array);

#endif
