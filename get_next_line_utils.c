#include "get_next_line.h"


void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*char_s;

	char_s = (char *)s;
	i = 0;
	while (i < n)
	{
		char_s[i] = c;
		i++;
	}
	return ((void *)char_s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;
	int		c;

	c = 0;
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr != NULL)
		ft_memset(ptr, c, total_size);
	return (ptr);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_src;
	char	*destiny;

	if (!s)
		return (NULL);
	i = 0;
	len_src = ft_strlen(s);
	if (start > len_src)
		return (ft_strdup(""));
	else if (start + len > len_src)
		len = len_src - start;
	destiny = ft_calloc(len + 1, sizeof(char));
	if ((!destiny))
		return (NULL);
	while (s[start] && i < len)
	{
		destiny[i] = s[start];
		i++;
		start++;
	}
	destiny[i] = '\0';
	return (destiny);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	count1;
	size_t	count2;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	count1 = 0;
	count2 = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (count1 != ft_strlen(s1))
	{
		s3[count1] = s1[count1];
		count1++;
	}
	while (count2 != ft_strlen(s2))
	{
		s3[count1 + count2] = s2[count2];
		count2++;
	}
	s3[count1 + count2] = '\0';
	return (s3);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*new_string;
	int		i;

	i = 0;
	new_string = (char *)malloc(ft_strlen(s1) + 1);
	if (!new_string) 
		return (NULL);
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
