#include "get_next_line.h"
#include <stdio.h>

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;
	char	*new_string;
	int		i;

	i = 0;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	if (content == NULL)
		new_string = malloc(1);
	else
	{
		new_string = (char *)malloc(ft_strlen(content) + 1);
		if (!new_string) 
			return (NULL);
		while (content[i] != '\0')
		{
			new_string[i] = content[i];
			i++;
		}
	}
	new_string[i] = '\0';
	new_node->content = new_string;
	new_node->bytes_read = 0;
	new_node->next = NULL;
	return (new_node);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (len > size)
		return ("");
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
void	clear_list(t_list *list)
{
	if (!list)
		return ;
	while (list)
	{
		free(list->content);
		list = list->next;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;
	size_t	len;

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
	return (joined);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	printf("FT_STRLEN %i\n", i);
	return (i);
}

