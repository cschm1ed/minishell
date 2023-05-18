#include <minishell.h>

static int go_up_one_dir(t_info *info);
static int go_to_home_dir(t_info *info);

int	execute_cd(t_info *info, char *dir)
{
	char *joined;

	if (!dir)
		return (go_to_home_dir(info));
	if (chdir(dir) == 0)
	{
		if (!ft_strcmp(dir, ".."))
			return (go_up_one_dir(info));
		else if (dir[0] == '.')
			return (0);
		else
		{
			joined = ft_strsjoin(info->pwd, "/", dir);
			if (joined == NULL)
				return (perror("malloc"), 1);
			info->pwd = joined;
			if (lst_replace_var_val(info->env_lst, "PWD", joined) == FAILURE)
				return (1);
			return (0);
		}
	}
	return (printf("minishell: cd: %s: %s\n", dir, strerror(errno)), 1);
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
		return (1);
	free (info->pwd);
	info->pwd = trimmed_pwd;
	if (lst_replace_var_val(info->env_lst, "PWD", trimmed_pwd) == FAILURE)
		return (1);
	return (0);
}

static int go_to_home_dir(t_info *info)
{
	char	*trimmed_pwd;
	int		delimiter;
	int		i;

	delimiter = 0;
	i = -1;
	while (info->pwd[++i] && delimiter <= 2)
		if (info->pwd[i] == '/')
			delimiter++;
	trimmed_pwd = ft_substr(info->pwd, 0, i - 1);
	if (trimmed_pwd == NULL)
		return (1);
	free (info->pwd);
	info->pwd = trimmed_pwd;
	if (lst_replace_var_val(info->env_lst, "PWD", trimmed_pwd) == FAILURE)
		return (1);
	return (0);
}
