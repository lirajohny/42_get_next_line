#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"

#include <stdio.h>
//#include <libc.h>

static int call = 1;
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
		//list->next = new;
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
	// new is a pointer to a new node
	t_list	*new;
	// BUFFER will store the buffer read each time 
	char *buffer;
	// will store the position of \n if there is
	int	pos;
	int loops = 1;
	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	// new will point to the last node of the list 
	new = ft_lstlast(*list);
	// if in the last call was content after the \n it was stored in list->remain
	// now it has to be moved to the next new node
	if (new->remain != NULL)
		new->content = ft_strjoin(new->content, new->remain); 
	while ((new->bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		loops++;
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
	if (pos <= new->bytes_read)
		new->remain = remain(buffer, pos + 1);
}

char	*get_next_line(int fd)
{
	call++;
	// QUESTIONS; AM I handeling the case where it doesnt find a line???
	// starts a static list *not a pointer to a list
	static t_list	list;
	// pointer to a list -> inicialized with NULL
	t_list	*head = NULL;
	// next_line is a pointer to the content of the last node (last line read)
	static char			*next_line;
	// this functions creates a new node each time
	head = &list;
	create_node("", &list); 
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	//read the file trying to find a line.
	read_file(&head, fd);
	// returns the last line read
	head = ft_lstlast(head);
	/* 
	clear the whole list when the EOF is reached
	clear_list(&list);
	*/
	if (head->bytes_read <= 0)
		return (NULL);
	next_line = head->remain;
	return (head->content);
}
