/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:47:45 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/07 15:47:45 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "../../libft/libft.h"

static void	print_variable(int fd_out, t_list *ptr);
static void	assign_pointers(t_info *info, char ***array,
				t_list **last, t_list **last2);

char	**cpy_lst_to_array(t_list *lst, char ***array)
{
	int		i;
	int		len;

	i = 0;
	if (ft_lstsize(lst) == 0)
		return (NULL);
	*array = ft_calloc(sizeof(char *), ft_lstsize(lst) + 1);
	if (!*array)
		return (perror("malloc"), NULL);
	len = ft_lstsize(lst);
	while (i < len)
	{
		(*array)[i++] = lst_get_var(lst)->name;
		lst = lst->next;
	}
	return (*array);
}

int	print_sorted_lst(t_info *info, int fd_out)
{
	int		i;
	char	**array;
	t_list	*last;
	t_list	*last2;
	t_list	*ptr;

	i = 0;
	assign_pointers(info, &array, &last, &last2);
	bubble_sort_str_array(array, ft_lstsize(info->env_lst));
	while (i < ft_lstsize(info->env_lst))
	{
		ptr = info->env_lst;
		while (ft_strcmp(lst_get_var(ptr)->name, array[i]) != 0)
			ptr = ptr->next;
		print_variable(fd_out, ptr);
		i++;
	}
	return (free(array), last2->next = NULL, last->next = NULL, SUCCESS);
}

static void	print_variable(int fd_out, t_list *ptr)
{
	ft_printf("declare -x %s", fd_out, lst_get_var(ptr)->name);
	if (lst_get_var(ptr)->value[0])
		ft_printf("=%s", fd_out, lst_get_var(ptr)->value);
	ft_printf("\n", fd_out);
}

int	check_if_varname_is_valid(char *str)
{
	int	i;

	i = 0;
	if ((ft_isalpha(str[0]) == FALSE)
		&& str[i] != '_')
		return (FALSE);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == FALSE
			&& str[i] != '_')
			return (FALSE);
		i ++;
	}
	return (TRUE);
}

static void	assign_pointers(t_info *info, char ***array,
				t_list **last, t_list **last2)
{
	(*last2)->next = info->user_vars;
	(*last) = ft_lstlast(info->env_lst);
	(*last)->next = info->export_lst;
	(*last2) = ft_lstlast(info->env_lst);
	if ((*array) == NULL)
	{
		(*last2)->next = NULL;
		(*last)->next = NULL;
		exit_error(info, __FILE__, __LINE__, "malloc");
	}
	(*array) = cpy_lst_to_array(info->env_lst, array);
}
