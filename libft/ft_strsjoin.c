#include "../includes/minishell.h"

char	*ft_strsjoin(const char *s1, const char *s2, const char *s3)
{
	char	*result;

	if (!s1)
		return (ft_strjoin(s2, s3));
	else if (!s2)
		return (ft_strjoin(s1, s3));
	else if (!s3)
		return (ft_strjoin(s1, s2));
	result = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1, 1);
	if (!result)
		return (NULL);
	ft_memmove(result, s1, ft_strlen(s1));
	ft_memmove(ft_strchr(result, 0), s2, ft_strlen(s2));
	ft_memmove(ft_strchr(result, 0), s3, ft_strlen(s3));
	return (result);
}
