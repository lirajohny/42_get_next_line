#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h>
#include "get_next_line.h"

int	find_line(char *str)
{
	int	index;
	
	index = 0;
	if (str[0] == '\n')
		return (0);
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			return (index);
			break;
		}
		index++;
	}
	return (0);
}

static char	*remain_line(char *backup)

{
	size_t	i;
	char	*rest;
	size_t	count;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!(backup[i]))
		return (NULL);
	if (backup[i] == '\n')
		i++;
	rest = malloc(sizeof(char) * ft_strlen(backup) - i + 1);
	if (!(rest))
		return (NULL);
	count = 0;
	while (backup[i])
		rest[count++] = backup[i++];
	rest[count] = '\0';
	return (rest);
}

char	*ft_get_line(struct s_list **list, int i, int j)
{
    t_list	*current;
	t_list	*head = *list;
	char	*result;
    int	len = 0;
	
	current = head;
	if (list == NULL)
        return NULL;
    while (current->next != NULL)
	{
        len += ft_strlen(current->content);
        current = current->next;
    }
	len = len + find_line(current->content);
	result = (char *)malloc(len + 2);
    result[0] = '\0';
    current = head;
    while (i < len + 1) 
	{
		j = 0;
		while (current->content[j] != '\0' && i < len + 1)
			result[i++] = current->content[j++]; 
        current = current->next;
    }
	result[i] = '\0';
    return result;			
}

int	read_file(t_list **list, int fd)
{
	t_list	*new;
	char	*buffer;
	int		pos;

	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (1);
	new = *list;
	while (1)
	{
		new->bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (new->bytes_read == 0)
		{
			free(buffer);
			return (1);
		}
		buffer[new->bytes_read] = '\0';
		pos = find_line(buffer);
		if (pos > 0 || buffer[0] == '\n')
		{
			new->next = ft_lstnew(buffer);
			break;
		}
		new->next = ft_lstnew(buffer);
		new = new->next;
	}
	free(buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	t_list	*head;
	char *next_line;
	static char*	remain;
	t_list	*last;
	static int	check_error;
	
	head = ft_lstnew(remain);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	check_error += read_file(&head, fd);
	if (check_error != 0)
	{
		if (check_error == 1)
		{
			check_error++;
			return (head->content);
		}
		ft_free(&head);
		return (NULL);
	}
	next_line = ft_get_line(&head, 0, 0);
	last = ft_lstlast(head);
	remain = remain_line(last->content);
	ft_free(&head);
	return (next_line);
}
