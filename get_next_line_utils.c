#include "get_next_line.h"
#include <stdio.h>

static int count_free = 0;
static int count_lstnew = 0;
void ft_free(t_list **list)
{
    t_list *current;
	t_list	*next;

	current = *list;
    while (current != NULL) 
	{
		count_free++;
		//printf("\033[1;31m FREE \033[0m >> %i <<\n", count_free);
		//printf("\tADDRESS | \033[1;36m %p \033[0m | LIBERANDO: |\033[1;36m %s \033[0m| \n", current->content, current->content);
        next = current->next;
        free(current->content);
        free(current);
        current = next;
    }
    list = NULL;
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
	count_lstnew++;
	//printf("\033[1;33m lst NEw FUNCTION \033[0m >> %i <<\n", count_lstnew);
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
	free(content);
	new_string[i] = '\0';
	new_node->content = new_string;
	//printf("\tADDRESS | \033[1;91m %p \033[0m | CRIANDO: |\033[1;36m %s \033[0m| \n", new_node->content, new_node->content);
	new_node->bytes_read = 0;
	new_node->next = NULL;
 	return (new_node);
 }
/*
t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;
	char	*new_string;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	if (content == NULL)
		new_string = ft_strdup("");
	else
		new_string = ft_strdup(content); 
	new_node->content = new_string;
	new_node->bytes_read = 0;
	new_node->next = NULL;
	return (new_node);
}*/

size_t	ft_strlen(char *s)
{
	int	i;

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
