#include "../../includes/minishell.h"

static void	go_up_one_dir(t_info *info);

int	execute_cd(t_info *info, char *dir)
{
	if (!chdir(dir))
	{
		if (!ft_strcmp(dir, ".."))
			go_up_one_dir(info);
		else if (dir[0] == '.')
			return (info->exit_code = 0, SUCCESS);
		else
			info->pwd = ft_strsjoin(info->pwd, "/", dir);
		return (info->exit_code = 0, SUCCESS);
	}
	return (printf("minishell: cd: %s: %s\n", dir, strerror(errno)), info->exit_code = 1, FAILURE);
}

static void	go_up_one_dir(t_info *info)
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