/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:56:19 by cschmied          #+#    #+#             */
/*   Updated: 2023/06/01 17:50:14 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		final_heredoc(t_info *info, t_list *heredocs, int hpipe[2]);
static int		compare_delimiter(const char *str, const char *delimiter);
static t_list	*ignore_multiple_heredocs(t_info *info, t_list *heredocs);

/**
 * @brief writes heredoc input into a pipe, the command will recieve
 * @param parsed
 * @param cnt
 * @param pipex
 * @param info
 * @return SUCCESS or FAILURE
 */
int	heredoc_redirect(t_list *parsed, int cnt, t_data *pipex, t_info *info)
{
	t_list	*heredocs;
	int		hpipe[2];

	heredocs = lst_get_parsed(parsed)->here_docs;
	if (cnt > 0)
	{
		read(pipex->pipe_fd[cnt - 1][0], NULL, 1);
		close(pipex->pipe_fd[cnt - 1][0]);
	}
	heredocs = ignore_multiple_heredocs(info, heredocs);
	if (pipe(hpipe) == -1)
		return (-1);
	return (final_heredoc(info, heredocs, hpipe));
}

/**
 * @brief writes heredoc input into a pipe, the command will recieve
 * @param info
 * @param heredocs
 * @param hpipe
 * @return SUCCESS or FAILURE
 */
static int	final_heredoc(t_info *info, t_list *heredocs, int hpipe[2])
{
	char	**buffer;

	buffer = ft_calloc(2, sizeof(char *));
	if (buffer == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		buffer[0] = get_next_line(STDIN_FILENO);
		if (buffer[0] == NULL)
			return (free(buffer), -1);
		if (replace_variables(info, buffer) == FAILURE)
		{
			free(buffer);
			exit_error(info, __FILE__, __LINE__, "malloc");
		}
		if (compare_delimiter(*buffer, lst_get_var(heredocs)->value) == 0)
			return (close(hpipe[1]), free(buffer), hpipe[0]);
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
				exit_error(info, __FILE__, __LINE__, "get next line");
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
