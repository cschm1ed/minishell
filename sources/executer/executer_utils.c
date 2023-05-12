/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:48:51 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/09 11:48:51 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_path(char *cmd, t_info *info)
{
	char *joined;
	char **paths;
	int  i;

	i = 0;
	paths = ft_split(lst_find_var_val(info->env_lst, "PATH"), ':');
	if (paths == NULL)
		return (perror("malloc"), NULL);
	while (paths[i])
	{
		joined = ft_strsjoin(paths[i], "/", cmd);
		if (joined == NULL)
			return (ft_free_dbl_ptr(paths), perror("malloc"), NULL);
		if (access(joined, F_OK) != -1)
			return (ft_free_dbl_ptr(paths), joined);
		i ++;
	}
	return (NULL);
}

int check_infiles(t_list *parsed)
{
	t_list  *redirects;
	char    *filename;
	int     fd;

	if (parsed == NULL)
		return (STDIN_FILENO);
	redirects = lst_get_parsed(parsed)->redirect_input;
	while (redirects)
	{
		filename = redirects->content;
		if (access(filename, F_OK) == -1 || access(filename, R_OK) == -1)
			return (printf("minishell: %s: %s\n", filename, strerror(errno)), FAILURE);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			return (printf("minishell: %s: :%s\n", filename, strerror(errno)));
		if (redirects != lst_get_parsed(ft_lstlast(parsed))->redirect_output)
			close(fd);
		redirects = redirects->next;
	}
	return (fd);
}

int create_outfiles(t_list *parsed)
{
	t_list  *redirects;
	char    *filename;
	int     fd;
	int		flags;

	if (parsed == NULL)
		return (STDIN_FILENO);
	redirects = lst_get_parsed(parsed)->redirect_output;
	while (redirects)
	{
		filename = lst_get_var(redirects)->name;
		if (access(filename, F_OK) != -1 && access(filename, W_OK) == -1) {
			return (printf("minishell: %s: %s\n", filename, strerror(errno)), FAILURE);
		}
		flags = O_WRONLY | O_TRUNC | O_CREAT;
		if (lst_get_var(redirects)->key == APPEND)
			flags = O_WRONLY | O_APPEND | O_CREAT;
		fd = open(filename, flags, 0644);
		if (fd == -1)
			return (printf("minishell: %s: :%s\n", filename, strerror(errno)));
		if (redirects != lst_get_parsed(ft_lstlast(parsed))->redirect_input)
			close(fd);
		redirects = redirects->next;
	}
	return (fd);
}

int **create_pipes(t_list *parsed)
{
	int i;
	int len;
	int **pipes;

	i = 0;
	len = ft_lstsize(parsed);
	pipes = ft_calloc(len, sizeof(int[2]));
	if (pipes == NULL)
		return (perror("malloc"), NULL);
	while (i < len)
	{
		pipes[i] = ft_calloc(1, sizeof(int[2]));
		if (pipe(pipes[i]) == -1)
			return (perror("pipe"), close_pipes(pipes), free(pipes), NULL);
		i ++;
	}
	return (pipes);
}

void    close_pipes(int **pipes)
{
	int i;

	i = 0;
	while (pipes[i])
	{
		if (pipes[i][0] != -1)
			close(pipes[i][0]);
		if (pipes[i][1] != -1)
			close(pipes[i][0]);
		pipes[i][0] = -1;
		pipes[i][1] = -1;
	}
}
