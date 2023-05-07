#include "../../includes/minishell.h"

char	*ft_strsjoin(const char *s1, const char *s2, const char *s3)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	if (!s1)
		return (ft_strjoin(s2, s3));
	else if (!s2)
		return (ft_strjoin(s1, s3));
	else if (!s3)
		return (ft_strjoin(s1, s2));
	result = malloc (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		result[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		result[i++] = s2[j];
	k = -1;
	while (s3[++k] != '\0')
		result[i++] = s3[k];
	result[i] = '\0';
	return (result);
}
