#include "get_next_line.h"
#include <stdio.h>

void ft_free(t_list **list)
{
	printf("\033[1;33m FREE  FUNCTION \033[0m\n");
    t_list *current;
	t_list	*next;

	current = *list;
    while (current != NULL) 
	{
        next = current->next;
		printf("\tADDRESS | \033[1;91m %p \033[0m |  LIBERANDO: |\033[1;36m %s \033[0m| \n", current->content, current->content);
        free(current->content);
        free(current);
        current = next;
    }
    list = NULL;
	printf("\033[1;33m LEAVING \033[0m\n");
}

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

