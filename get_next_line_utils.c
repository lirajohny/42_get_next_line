#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*pointer;
	int		counter;

	counter = 0;
	pointer = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!pointer)
		return (NULL);
	if (s1)
	{
		while (s1[counter])
		{
			pointer[counter] = s1[counter];
			counter++;
		}
		free(s1);
	}
	while (*s2)
		pointer[counter++] = *s2++;
	pointer[counter] = '\0';
	if (!*pointer)
	{
		free(pointer);
		return (NULL);
	}
	return (pointer);
}

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

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	size;
	size_t	counter;

	counter = 0;
	size = ft_strlen(src);
	if (dstsize == 0)
		return (size);
	while (counter < size && counter < dstsize - 1)
	{
		dst[counter] = src[counter];
		counter++;
	}
	dst[counter] = '\0';
	return (size);
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
	char	*pointer;
	int		counter;

	pointer = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!pointer)
		return (NULL);
	counter = 0;
	while (s1[counter] != '\0')
	{
		pointer[counter] = s1[counter];
		counter++;
	}
	pointer[counter] = '\0';
	return (pointer);
}
