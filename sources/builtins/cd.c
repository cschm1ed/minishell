#include <minishell.h>

static int	update_env(t_info *info);

int	execute_cd(t_info *info, char *dir)
{
	t_variable*	variable;

	variable = (t_variable*)lst_find_node(info->env_lst, "USER")->content;
	if (!dir)
		dir = ft_strjoin("/Users/", variable->value);
	if (!chdir(dir))
		return (update_env(info));
	return (ft_printf("minishell: cd: %s: %s\n", dir, strerror(errno)), 1);
}

static int	update_env(t_info *info)
{
	char	*updated_pwd;

	updated_pwd = getcwd(NULL, 0);
	if (!updated_pwd)
		return (perror("minishell: cd"), 1);
	free (info->pwd);
	info->pwd = updated_pwd;
	if (lst_replace_var_val(info->env_lst, "PWD", updated_pwd) == FAILURE)
		return (1);
	return (0);
}
