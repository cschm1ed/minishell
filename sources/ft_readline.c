/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:42:12 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/24 18:05:36 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char    *ft_readline(const char *str)
{
    char    *tmp;

    tmp = readline(str);
    add_history(tmp);
    return (tmp);
}