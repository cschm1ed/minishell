#include "../../includes/minishell.h"

static void	terminate_string(char *s, size_t *i);
static char *allocate_string(char *s, size_t *i, size_t *start);

int	count_substrs(char *s)
{
	int		cnt;
	size_t	i;

	cnt = 0;
	i = -1;
	while (s[++i])
		if (!ft_isspace(s[i]))
		{
			cnt++;
			terminate_string(s, &i);
			if (s[i - 1] && ft_isspecial(s[i]) && !ft_isspace(s[i - 1]))
				cnt++;
			skip_specials(s, &i);
		}
	return (cnt);
}

char	**split_if_isspace(char **split, char *s, int amt_substrs)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (s[++i] && (int) j < amt_substrs)
		if (s[i] && !ft_isspace(s[i]))
		{
			start = i;
			terminate_string(s, &i);
			if (s[i - 1] && ft_isspecial(s[i]) && !ft_isspace(s[i - 1]))
			{
				split[j] = ft_substr(s, start, i - start);
				if (!split[j++])
					return (ft_free_dbl_ptr(split));
				start =  i;
			}
			split[j] = allocate_string(s, &i, &start);
			if (!split[j++])
				return (ft_free_dbl_ptr(split));
		}
	split[j] = NULL;
	return (split);
}

static void	terminate_string(char *s, size_t *i)
{
	while (s[*i] && !ft_isspace(s[*i]) && !ft_isspecial(s[*i]))
	{
		if (ft_isquote(s[*i]))
			skip_until_quote(s, i);
		(*i)++;
	}
}

static char *allocate_string(char *s, size_t *i, size_t *start)
{
	char *split;

	if (ft_isspecial(s[*i]) && skip_specials(s, i))
		split = ft_substr(s, *start, (*i + 1) - *start);
	else
		split = ft_substr(s, *start, *i - *start);
	return (split);
}
