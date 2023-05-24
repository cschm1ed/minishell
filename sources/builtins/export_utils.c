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

char	**cpy_lst_to_array(t_list *lst, char ***array)
{
	int		i;
	char	**arr;
	int		len;

	i = 0;
	arr = ft_calloc(sizeof(char *), ft_lstsize(lst) + 1);
	if (!arr)
		return (perror("malloc"), NULL);
	len = ft_lstsize(lst);
	while (i < len)
	{
		arr[i++] = lst_get_var(lst)->name;
		lst = lst->next;
	}
	*array = arr;
	return (arr);
}

int	print_sorted_lst(t_info *info, int fd_out)
{
	int		i;
	char	**array;
	t_list	*last;
	t_list	*ptr;

	i = 0;
	last = ft_lstlast(info->env_lst);
	last->next = info->export_lst;
	if (cpy_lst_to_array(info->env_lst, &array) == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	bubble_sort_str_array(array, ft_lstsize(info->env_lst));
	while (i < ft_lstsize(info->env_lst))
	{
		ptr = info->env_lst;
		while (ft_strcmp(lst_get_var(ptr)->name, array[i++]) != 0)
			ptr = ptr->next;
		print_variable(fd_out, ptr);
	}
	free(array);
	last->next = NULL;
	return (SUCCESS);
}

static void	print_variable(int fd_out, t_list *ptr)
{
	ft_putstr_fd("declare -x ", fd_out);
	ft_putstr_fd(lst_get_var(ptr)->name, fd_out);
	if (lst_get_var(ptr)->value[0])
	{
		ft_putstr_fd("=", fd_out);
		ft_putstr_fd(lst_get_var(ptr)->value, fd_out);
	}
	ft_putchar_fd('\n', fd_out);
}

int	check_if_varname_is_valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == FALSE
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

/**
 * @brief Adds a list of variables to a linked list.
 *
 * @param list A pointer to a pointer to the head of the linked list.
 * @param arg An array of strings containing variable assignments in the
 * 								format "name=value".
 *
 * @return SUCCESS if all variables are added successfully, or
 * 											FAILURE if an error occurs.
 */
int	var_lst_add(t_list **list, char **arg)
{
	t_variable	*var;
	char		**split;
	int			i;

	i = 0;
	while (arg[i])
	{
		split = ft_split(arg[i], '=');
		if (!split)
			return (perror("malloc"), FAILURE);
		var = ft_calloc(sizeof(t_variable), 1);
		if (!var)
			return (perror("malloc"), FAILURE);
		var->name = ft_strdup(split[0]);
		var->value = ft_strdup(split[1]);
		ft_free_dbl_ptr(split);
		ft_lstadd_back(list, ft_lstnew((void *)(var)));
		i ++;
	}
	return (SUCCESS);
}
