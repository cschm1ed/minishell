/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:56:19 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/24 18:38:01 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		compare_delimiter(const char *str, const char *delimiter);
static t_list	*ignore_multiple_heredocs(t_info *info, t_list *heredocs);

int	heredoc_redirect(t_list *parsed, int cnt, t_data *pipex, t_info *info)
{
	char	**buffer;
	t_list	*heredocs;
	int		hpipe[2];

	buffer = ft_calloc(2, sizeof(char *));
	if (buffer == NULL)
		exit_error(info, __FILE__, __LINE__, "malloc");
	heredocs = lst_get_parsed(parsed)->here_docs;
	if (cnt > 0)
	{
		read(pipex->pipe_fd[cnt - 1][0], NULL, 1);
		close(pipex->pipe_fd[cnt - 1][0]);
	}
	heredocs = ignore_multiple_heredocs(info, heredocs);
	if (pipe(hpipe) == -1)
		return (free(buffer), -1);
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		buffer[0] = get_next_line(STDIN_FILENO);
		if (buffer[0] == NULL)
			return (free(buffer), -1);
		if (ft_strchr(buffer[0], '$'))
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

static int	compare_delimiter(const char *str, const char *delimiter)
{
	int	i;

	i = 0;
	while (str[i] == delimiter[i])
		i ++;
	if (str[i] == '\n' && str[i + 1] == 0)
		return (0);
	return (1);
}

static t_list	*ignore_multiple_heredocs(t_info *info, t_list *heredocs)
{
	char	*buffer;

	while (heredocs->next)
	{
		while (1)
		{
			ft_putstr_fd("> ", STDIN_FILENO);
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
