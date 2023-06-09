/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:48:51 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/14 12:52:23 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define EMSG1 "minishell: %s: No such file or directory\n"
#define EMSG2 "minishell: %s: permission denied\n"
#define EMSG3 "minishell no access: %s: %s\n"
#define EMSG4 "minishell open failed: %s: :%s\n"

int	check_infiles(t_list *parsed)
{
	t_list	*redirects;
	char	*fname;
	int		fd;

	fd = STDIN_FILENO;
	redirects = lst_get_parsed(parsed)->redirect_input;
	if (lst_get_parsed(parsed)->hdoc == TRUE)
		return (lst_get_parsed(parsed)->heredoc_pipe[0]);
	if (redirects == NULL && lst_get_parsed(parsed)->here_docs == NULL)
		return (STDIN_FILENO);
	while (redirects)
	{
		fname = lst_get_var(redirects)->value;
		if (access(fname, F_OK) == -1)
			return (ft_printf(EMSG1, 2, fname), -1);
		else if (access(fname, R_OK) == -1)
			return (ft_printf(EMSG2, 2, fname), -1);
		fd = open(fname, O_RDONLY);
		if (fd == -1)
			return (perror("minishell: open: "), -1);
		if (redirects != ft_lstlast(redirects))
			close(fd);
		redirects = redirects->next;
	}
	return (fd);
}

int	create_outfiles(t_list *parsed)
{
	t_list	*redirects;
	char	*fname;
	int		fd;
	int		flags;

	redirects = lst_get_parsed(parsed)->redirect_output;
	fd = STDOUT_FILENO;
	while (redirects)
	{
		fname = lst_get_var(redirects)->value;
		if (access(fname, F_OK) != -1 && access(fname, W_OK) == -1)
			return (ft_printf(EMSG3, 2, fname, strerror(errno)), -1);
		flags = O_WRONLY | O_TRUNC | O_CREAT;
		if (lst_get_var(redirects)->key == APPEND)
			flags = O_WRONLY | O_APPEND | O_CREAT;
		fd = open(fname, flags, 0644);
		if (fd == -1)
			return (ft_printf(EMSG4, 2, fname, strerror(errno)), -1);
		if (redirects != ft_lstlast(redirects))
			close(fd);
		redirects = redirects->next;
	}
	return (fd);
}

int	handle_files(t_data *pipex, t_list *parsed)
{
	pipex->file_fd[0] = check_infiles(parsed);
	if (pipex->file_fd[0] == -1)
		return (FAILURE);
	pipex->file_fd[1] = create_outfiles(parsed);
	if (pipex->file_fd[1] == -1)
		return (FAILURE);
	return (SUCCESS);
}
