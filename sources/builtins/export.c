/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:24:23 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/28 23:24:23 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_sorted_lst(t_info *info);
static char	**cpy_lst_to_array(t_list *lst);
static void	bubble_sort_str_array(char **array, int len);
static int	check_if_arg_is_valid(char *arg);

int	export(t_info *info, char **arg)
{
	int i;

	i = 0;
	if (arg == NULL)
		return (print_sorted_lst(info));
	while (arg[i])
	{
		if (check_if_arg_is_valid(*arg) == FALSE)
		{
			printf("minishell: export: '%s': not a valid identifier\n", arg[i]);
			return (FAILURE);
		}
		i ++;
	}
	return (var_lst_add(&(info->env_lst), arg));
}

static char	**cpy_lst_to_array(t_list *lst)
{
	int		i;
	char	**arr;
	int		len;

	i = 0;
	arr = ft_calloc(sizeof(char*), ft_lstsize(lst) + 1);
	if (!arr)
		return (perror("malloc"), NULL);
	len = ft_lstsize(lst);
	while (i < len)
	{
		arr[i] = lst_get_var(lst)->name;
		i ++;
		lst = lst->next;
	}
	return (arr);
}

static void	bubble_sort_str_array(char **array, int len)
{
	int 	i;
	int		j;
	char 	*tmp;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			if (ft_strncmp(array[j], array[j + 1], ft_strlen(array[j])) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j ++;
		}
		i ++;
	}
}

static int	print_sorted_lst(t_info *info)
{
	int 	i;
	char 	**array;
	t_list	*ptr;

	i = 0;
	array = cpy_lst_to_array(info->env_lst);
	if (!array)
		return (FAILURE);
	i = 0;
	bubble_sort_str_array(array, ft_lstsize(info->env_lst));
	while (i < ft_lstsize(info->env_lst))
	{
		ptr = info->env_lst;
		while (ft_strncmp(lst_get_var(ptr)->name, array[i], ft_strlen(array[i])) != 0)
			ptr = ptr->next;
		printf("declare -x %s=%s\n", lst_get_var(ptr)->name, lst_get_var(ptr)->value);
		i ++;
	}
	return (SUCCESS);
}

static int check_if_arg_is_valid(char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]) == FALSE
		&& str[i] != '_')
		return (FALSE);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == FALSE
			&& str[i] != '_')
			return (FALSE);
		i ++;
	}
	return (TRUE);
}
