#include "../../includes/minishell.h"

static	int go_up_one_dir(t_info *info, char *dir)
{
	char	*trimmed_pwd;
	char	*current_dir;
	size_t	len;

	current_dir = ft_strrchr(info->pwd, '/');
	len = ft_strlen(info->pwd) - ft_strlen(current_dir);
	trimmed_pwd = ft_substr(info->pwd, 0, len);
	free (info->pwd);
	info->pwd = trimmed_pwd;
}

int	execute_cd(t_info *info, char *dir)
{
	if (!chdir(dir))
	{
		if (!ft_strcmp(dir, ".."))
			go_up_one_dir(info, dir);
		else if (dir[0] == '.')
			return (SUCCESS);
		else
			info->pwd = ft_strsjoin(info->pwd, "/", dir);
		return (SUCCESS);
	}
	return (printf("minishell: cd: %s: %s\n", dir, strerror(errno)),
		info->exit_code = 1, FAILURE);
}