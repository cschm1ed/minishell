/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:48:50 by cschmied          #+#    #+#             */
/*   Updated: 2023/05/30 15:45:51 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*var_list_init(char **env);
static int		update_shlvl(t_info *info);

/**
 * @brief Initializes an info struct with a list of variables from an
 * 										environment array.
 *
 * @param info A pointer to the info struct to be initialized.
 * @param env The environment array.
 *
 * @return SUCCESS if successful, FAILURE otherwise.
 */
t_info	*info_init(char **env)
{
	t_info	    *info;

	info = ft_calloc(sizeof(t_info), 1);
	if (info == NULL)
		return (perror("malloc"), NULL);
	info->builtins = ft_calloc(8, sizeof(t_command));
	if (info->builtins == NULL)
		return (perror("malloc"), NULL);
	info->builtins[0] = (t_command){"echo", execute_echo};
	info->builtins[1] = (t_command) {"env", execute_env};
	info->builtins[2] = (t_command) {"cd", execute_cd};
	info->builtins[3] = (t_command){"exit", execute_exit};
	info->builtins[4] = (t_command){"export", execute_export};
	info->builtins[5] = (t_command) {"pwd", execute_pwd};
	info->builtins[6] = (t_command){"unset", execute_unset};
	info->builtins[7] = (t_command){NULL, NULL};
	info->env_lst = var_list_init(env);
	if (info->env_lst == NULL)
		return (NULL);
	info->pwd = ft_strdup(lsts_find_var_val(info, "PWD") );
	if (!info->pwd || update_shlvl(info) == FAILURE)
		return (perror("malloc"), NULL);
	info->env = env;
	return (info);
}

/**
 * @brief Initializes a list of variables from an environment array.
 *
 * @param env The environment array.
 *
 * @return A pointer to the initialized list of variables.
 */
static t_list	*var_list_init(char **env)
{
	t_list		*ret;

	ret = NULL;
	if (var_lst_add(&ret, env) == FAILURE)
		return (ft_lstclear(&ret, delete_variable), NULL);
	return (ret);
}

static int	update_shlvl(t_info *info)
{
	char	*val;
	char	*new;
	int		x;

	val = lst_find_var_val(info->env_lst, "SHLVL");
	if (val)
	{
		x = ft_atoi(val);
		new = ft_itoa(x + 1);
		if (new == NULL)
			return (FAILURE);
		if (val)
		{
			free(val);
			lst_replace_var_val(info->env_lst, "SHLVL", new);
		}
	}
	return (SUCCESS);
}

/**
 * frees all memory, a s_variable struct holds.
 *
 * @param content pointer to the struct to be deleted.
 */
void	delete_variable(void *content)
{
	t_variable	*ptr;

	ptr = (t_variable *)content;
	if (ptr == NULL)
		return ;
	if (ptr->name)
		free(ptr->name);
	if (ptr->value)
		free(ptr->value);
	ptr->name = NULL;
	ptr->value = NULL;
	free(ptr);
}

/**
 * frees all memory held by a s_parsed struct.
 *
 * @param content - pointer to the struct to be freed
 */
void	delete_parsed(void *content)
{
	t_parsed	*parsed;

	parsed = (t_parsed *)content;
	if (parsed == NULL)
		return ;
	if (parsed->args)
		ft_free_dbl_ptr(&parsed->args);
	if (parsed->cmd)
		free(parsed->cmd);
	if (parsed->redirect_input)
		ft_lstclear(&(parsed->redirect_input), delete_variable);
	if (parsed->redirect_output)
		ft_lstclear(&(parsed->redirect_output), delete_variable);
	if (parsed->here_docs)
		ft_lstclear(&parsed->here_docs, delete_variable);
	if (content)
		free(content);
	ft_bzero(parsed, sizeof(parsed));
}
