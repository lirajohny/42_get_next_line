#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*new_string;
	int		i;

	i = 0;
	new_string = (char *)malloc(ft_strlen(s1) + 1);
	if (new_string == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
