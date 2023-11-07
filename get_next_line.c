#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"

#include <stdio.h>

char	*remain(char *buffer, int pos)
{
	int i;
	char *remain;
	int	len;

	len = ft_strlen(buffer + pos);
	i = 0;
	remain = malloc(sizeof(char) * len + 1);
	if (!remain || !buffer)
		return (NULL);
	while(buffer[pos + i] != '\0')
	{
		remain[i] = buffer[pos + i];
		i++;
	}
	remain[i] = '\0';
	return (remain);
}

char *read_line(char *str, int pos)
{
	char buffer[pos + 1];
	int	i;

	i = 0;
	if (!str || pos < 0)
		return (NULL);
	while (str[i] != '\n')
	{
		buffer[i] = str[i];
		i++;
	}
	buffer[i++] = '\n';
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

int	find_line(char *str)
{
	int	index;
	
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			return (index);
			break;
		}
		index++;
	}
	return (-1);
}

char	*get_line(t_list *list)
{
	t_list	*ptr;
	ptr = ft_lstlast(list);
	
	return (ptr->content);
}

void create_node(char *str, t_list *list)
{
	t_list *new;
	t_list *last;

	if (list->next == NULL)
	{
		list->content = "";
		list->bytes_read = 0;
		return ;
	}
	new = ft_lstnew(str);
	last = ft_lstlast(list);
	if (last->remain != NULL)
	{
		new->remain = ft_strdup(last->remain);
		free(last->remain);
	}
	return ;
}
void read_file(t_list **list, int fd)
{
	t_list	*new;
	char *buffer;
	int	pos;
	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	new = ft_lstlast(*list);
	if (new->remain != NULL)
		new->content = ft_strjoin(new->content, new->remain); 
	while ((new->bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[new->bytes_read] = '\0';
		pos = find_line(buffer);
		if (pos >= 0)
		{
			new->content = ft_strjoin(new->content, read_line(buffer, pos + 1));
			break;
		}
		new->content = ft_strjoin(new->content, buffer);
	}
	if (pos <= new->bytes_read)
		new->remain = remain(buffer, pos + 1);
}

char	*get_next_line(int fd)
{
	static t_list	list;
	t_list	*head = NULL;
	static char			*next_line;
	head = &list;
	create_node("", &list); 
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	read_file(&head, fd);
	head = ft_lstlast(head);
	if (head->bytes_read <= 0)
	{
		return (NULL);
		clear_list(&list);
	}
	next_line = head->remain;
	return (head->content);
}
