/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:56:19 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/19 09:44:53 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		final_heredoc(t_info *info, t_list *heredocs, int *hpipe);
static int		compare_delimiter(const char *str, const char *delimiter);
static t_list	*ignore_multiple_heredocs(t_info *info, t_list *heredocs);
void			execute_heredoc(t_list *parsed, t_data *pipex, t_info *info);

/**
 * @brief writes heredoc input into a pipe, the command will recieve
 * @param parsed
 * @param cnt
 * @param pipex
 * @param info
 * @return SUCCESS or FAILURE
 */
int	heredoc_redirect(t_list *parsed, t_data *pipex, t_info *info)
{
	int	status;

	status = 0;
	while (parsed)
	{
		if (lst_get_parsed(parsed)->here_docs)
		{
			execute_heredoc(parsed, pipex, info);
			ft_lstclear(&lst_get_parsed(parsed)->redirect_input,
				delete_variable);
			lst_get_parsed(parsed)->redirect_input = NULL;
			ft_lstclear(&lst_get_parsed(parsed)->here_docs, delete_variable);
			lst_get_parsed(parsed)->here_docs = NULL;
			lst_get_parsed(parsed)->hdoc = TRUE;
			setup_signals(keybindings_ignore);
			waitpid(pipex->heredoc_pid, &status, 0);
			setup_signals(keybindings_parent);
			if ((((*(int *)&(status)) & 0177) == 0))
				g_exit_code = (((*(int *)&(status)) >> 8) & 0x000000ff);
		}
		parsed = parsed->next;
	}
	return (SUCCESS);
}

void	execute_heredoc(t_list *parsed, t_data *pipex, t_info *info)
{
	t_list	*heredocs;

	heredocs = lst_get_parsed(parsed)->here_docs;
	setup_signals(keybindings_heredoc);
	if (pipex->heredoc_pid == -1
		|| pipe(lst_get_parsed(parsed)->heredoc_pipe) != 0)
		exit_error(info, __FILE__, __LINE__, "fork/pipe");
	pipex->heredoc_pid = fork();
	if (pipex->heredoc_pid == 0)
	{
		heredocs = lst_get_parsed(parsed)->here_docs;
		heredocs = ignore_multiple_heredocs(info, heredocs);
		if (final_heredoc(info, heredocs, lst_get_parsed(parsed)->heredoc_pipe)
			== FAILURE)
			execute_exit_child(info, NULL, 1);
		close(lst_get_parsed(parsed)->heredoc_pipe[0]);
		execute_exit_child(info, NULL, 0);
	}
	close(lst_get_parsed(parsed)->heredoc_pipe[1]);
}

/**
 * @brief writes heredoc input into a pipe, the command will recieve
 * @param info
 * @param heredocs
 * @param hpipe
 * @return SUCCESS or FAILURE
 */
static int	final_heredoc(t_info *info, t_list *heredocs, int *hpipe)
{
	char	*buffer[2];

	buffer[1] = NULL;
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		buffer[0] = get_next_line(STDIN_FILENO);
		if (buffer[0] == NULL)
			return (FAILURE);
		if (replace_variables(info, buffer) == FAILURE)
		{
			free(buffer[0]);
			exit_error(info, __FILE__, __LINE__, "malloc");
		}
		if (compare_delimiter(*buffer, lst_get_var(heredocs)->value) == 0)
			return (close(hpipe[1]), free(buffer[0]), SUCCESS);
		write(hpipe[1], buffer[0], ft_strlen(buffer[0]));
		free(buffer[0]);
	}
	return (SUCCESS);
}

/**
 * @brief checks if the given string matches the heredoc delimiter
 * @param str
 * @param delimiter
 * @return TRUE or FALSE
 */
static int	compare_delimiter(const char *str, const char *delimiter)
{
	if (strnstr(str, delimiter, ft_strlen(delimiter)) == str
		&& *(str + ft_strlen(delimiter)) == '\n'
		&& *(str + ft_strlen(delimiter) + 1) == 0)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief ignores multiple heredocs, so only input from last
 * 			heredoc will be recieved
 * @param info
 * @param heredocs
 * @return
 */
static t_list	*ignore_multiple_heredocs(t_info *info, t_list *heredocs)
{
	char	*buffer;

	while (heredocs->next)
	{
		while (1)
		{
			ft_printf("> ", STDIN_FILENO);
			buffer = get_next_line(STDIN_FILENO);
			if (buffer == NULL)
				execute_exit_child(info, NULL, 1);
			if (compare_delimiter(buffer, lst_get_var(heredocs)->value) == 0)
			{
				free(buffer);
				break ;
			}
			free(buffer);
		}
		heredocs = heredocs->next;
	}
	return (heredocs);
}
