#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc(sizeof(char) * len + 1);
	if (!joined)
		return (NULL);
	while (i < len)
	{
		if (i < ft_strlen(s1))
			joined[i] = s1[i];
		else
		{
			joined[i] = s2[j++];
		}
		i++;
	}
	joined[i] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (joined);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (len > size)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
	{
	//	free(str);
		return (NULL);
	}
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	free((char *)s);
	return (str);
}
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
	if (!new_string) 
	{
	//	free(new_string);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	new_string[i] = '\0';
	free((char *)s1);
	return (new_string);
}
