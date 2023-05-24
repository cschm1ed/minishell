/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:48:51 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/24 18:29:41 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_infiles(t_list *parsed, int cnt, t_data *pipex, t_info *info)
{
	t_list	*redirects;
	char	*filename;
	int		fd;

	redirects = lst_get_parsed(parsed)->redirect_input;
	if (redirects == NULL && lst_get_parsed(parsed)->here_docs == NULL)
		return (STDIN_FILENO);
	while (redirects)
	{
		filename = lst_get_var(redirects)->value;
		if (access(filename, F_OK) == -1 || access(filename, R_OK) == -1)
			return (ft_printf("minishell: %s: %s\n",
					filename, strerror(errno)), -1);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			return (ft_printf("minishell: %s: :%s\n",
					filename, strerror(errno)), -1);
		if (redirects != ft_lstlast(redirects))
			close(fd);
		redirects = redirects->next;
	}
	if (lst_get_parsed(parsed)->here_docs != NULL)
		fd = heredoc_redirect(parsed, cnt, pipex, info);
	return (fd);
}

int	create_outfiles(t_list *parsed)
{
	t_list	*redirects;
	char	*filename;
	int		fd;
	int		flags;

	redirects = lst_get_parsed(parsed)->redirect_output;
	if (redirects == NULL)
		return (STDOUT_FILENO);
	while (redirects)
	{
		filename = lst_get_var(redirects)->value;
		if (access(filename, F_OK) != -1 && access(filename, W_OK) == -1)
			return (ft_printf("minishell no access: %s: %s\n",
					filename, strerror(errno)), -1);
		flags = O_WRONLY | O_TRUNC | O_CREAT;
		if (lst_get_var(redirects)->key == APPEND)
			flags = O_WRONLY | O_APPEND | O_CREAT;
		fd = open(filename, flags, 0644);
		if (fd == -1)
			return (ft_printf("minishell open failed: %s: :%s\n",
					filename, strerror(errno)), -1);
		if (redirects != ft_lstlast(redirects))
			close(fd);
		redirects = redirects->next;
	}
	return (fd);
}

int	**create_pipes(t_list *parsed)
{
	int	i;
	int	len;
	int	**pipes;

	i = 0;
	len = ft_lstsize(parsed);
	pipes = ft_calloc(len, sizeof(int [2]));
	if (pipes == NULL)
		return (perror("malloc"), NULL);
	while (i < len)
	{
		pipes[i] = ft_calloc(1, sizeof(int [2]));
		if (pipe(pipes[i]) == -1)
			return (perror("pipe"), close_pipes(pipes), free(pipes), NULL);
		i ++;
	}
	return (pipes);
}

void	close_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		if (pipes[i][0] != -1)
			close(pipes[i][0]);
		if (pipes[i][1] != -1)
			close(pipes[i][0]);
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i ++;
	}
}

void	handle_files(t_data *pipex, t_list *parsed, t_info *info, int cnt)
{
	pipex->file_fd[0] = check_infiles(parsed, cnt, pipex, info);
	if (pipex->file_fd[0] == -1 && parsed->next == NULL)
		execute_exit(info, NULL, 1);
	pipex->file_fd[1] = create_outfiles(parsed);
	if (pipex->file_fd[1] == -1)
		execute_exit(info, NULL, 1);
}
