#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"
//#include <libc.h>

char	*remain(char *buffer, int pos)
{
	int i;
	char *remain;
	int	len;
	
	if (!buffer)
		return (NULL);
	len = ft_strlen(buffer + pos);
	i = 0;
	remain = malloc(sizeof(char) * len + 1);
	if (!remain || len == 0)
	{
		free(remain);
		return (NULL);
	}
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

t_list *create_node(void)
{
	static t_list	*list;
	t_list *new;
	t_list *last;

	if (list == NULL)
	{
		list = malloc(sizeof(t_list));
		list->content = ft_strdup("");
		list->bytes_read = -1;
		return list;
	}
	last = ft_lstlast(list);
	if (last->bytes_read == 0)
	{
		clear_list(list);
		return (NULL);
	}
	new = ft_lstnew();
	if (last->remain != NULL || last->bytes_read == -2)
	{
		if (last->bytes_read == 0 && last->content != NULL)
		{
			last->remain = ft_strdup(last->content);
			last->content = NULL;
			return (list);
		}
		new->content = ft_strdup(last->remain);
	}
	if (new->content == NULL)
		new->content = ft_strdup("");
	last->next = new;
	return (list);
}

char *read_file(t_list **list, int fd)
{
	t_list	*new;
	char *buffer;
	int	pos;
	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	new = ft_lstlast(*list);
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
	if (pos != -1 && pos + 1 < new->bytes_read)
		new->remain = remain(buffer, pos + 1);
	return (new->content);
}

char	*get_next_line(int fd)
{
	t_list	*head = NULL;
	static char			*next_line;

	head = create_node(); 
	if (head == NULL)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	next_line = read_file(&head, fd);
	return (next_line);
}
