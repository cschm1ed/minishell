#include <minishell.h>

static int go_up_one_dir(t_info *info);

int	execute_cd(t_info *info, char *dir)
{
	char *joined;

	if (chdir(dir) == 0)
	{
		if (!ft_strcmp(dir, ".."))
		{
			if (go_up_one_dir(info) == FAILURE)
				return (FAILURE);
		}
		else if (dir[0] == '.')
			return (info->exit_code = 0, SUCCESS);
		else
		{
			joined = ft_strsjoin(info->pwd, "/", dir);
			if (joined == NULL)
				return (perror("malloc"), FAILURE);
			info->pwd = joined;
			if (lst_replace_var_val(info->env_lst, "PWD", joined) == FAILURE)
				return (FAILURE);
		}
		// printf(GREEN"PWD: %s\n"ESC, info->pwd);

		return (info->exit_code = 0, SUCCESS);
	}
	return (printf("minishell: cd: %s: %s\n", dir, strerror(errno)), info->exit_code = 1, FAILURE);
}

static int go_up_one_dir(t_info *info)
{
	char	*trimmed_pwd;
	char	*current_dir;
	size_t	len;

	current_dir = ft_strrchr(info->pwd, '/');
	len = ft_strlen(info->pwd) - ft_strlen(current_dir);
	trimmed_pwd = ft_substr(info->pwd, 0, len);
	if (trimmed_pwd == NULL)
		return (FAILURE);
	free (info->pwd);
	info->pwd = trimmed_pwd;
	if (lst_replace_var_val(info->env_lst, "PWD", trimmed_pwd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
