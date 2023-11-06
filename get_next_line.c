#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"

#include <stdio.h>
//#include <libc.h>

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
	if (!str || pos < 0)
		return (NULL);
	return (ft_substr(str, 0, pos));
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

t_list *create_node(char *str, t_list **list)
{
	t_list *new;
	t_list *last;

	new = ft_lstnew(str);
	last = ft_lstlast(*list);
	last->next = new;

	return (new);
}

void read_file(t_list **list, int fd)
{
	// new is a pointer to a new node
	t_list	*new;
	// BUFFER will store the buffer read each time 
	char *buffer;
	// will store the position of \n if there is
	size_t	pos;

	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	// at first new will be the last node of the list
	new = ft_lstlast(*list);
		printf("debug\n");
	//printf("new -> %s\n" new->content);
	// if in the last call was content after the \n it was stored in list->remain
	// now it has to be moved to the next new node
	if (new->remain != NULL)
	{
		new = create_node(new->remain, list);
	}
	else// creates a new node
	{
		printf("\t\t\ttrying to create node\n");
		new = create_node("", list);
		printf("\t\t\tnode create - content = %s\n",new->content);
	}
	while ((new->bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[new->bytes_read] = '\0';
		pos = find_line(buffer);
		if (pos >= 0)
		{
			//when \n is found it will update the value of content with
			//the string inside buffer until POS
			new->content = ft_strjoin(new->content, read_line(buffer, pos + 1));
			break;
		}
		// while \n is not found it will concatenate the content of buffer
		new->content = ft_strjoin(new->content, buffer);
	}
	// updates the content of remain if there is
	if (pos < ft_strlen(buffer))
		new->remain = remain(buffer, pos + 1);
	free(buffer);
}

char	*get_next_line(int fd)
{
	// starts a static list initialized with NULL
	static t_list	list;
	t_list	*head;
	// next_line is a pointer to the content of the last node (last line read)
	char			*next_line;

	list = create_node("", &list); 
	head = &list;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	//read the file trying to find a line.
	printf("GNL START\n");
	read_file(&head, fd);
	if (list == NULL)
		return (NULL);
	// returns the last line read
	next_line = get_line(head);
	// clear the whole list when the EOF is reached
	clear_list(list);
	return (next_line);
}
