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

char	**cpy_lst_to_array(t_list *lst)
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

void	bubble_sort_str_array(char **array, int len)
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

int	print_sorted_lst(t_info *info)
{
	int 	i;
	char 	**array;
	t_list	*last;
	t_list	*ptr;

	i = 0;
	last = ft_lstlast(info->env_lst);
	last->next = info->export_lst;
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
		if (lst_get_var(ptr)->value[0])
			printf("declare -x %s=%s\n", lst_get_var(ptr)->name, lst_get_var(ptr)->value);
		else
			printf("declare -x %s\n", lst_get_var(ptr)->name);
		i ++;
	}
	free(array);
	last->next = NULL;
	return (SUCCESS);
}

int check_if_varname_is_valid(char *str)
{
	int i;

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
