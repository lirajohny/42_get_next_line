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
			return (index);
		index++;
	}
	return (0);
}

static char	*remain_line(char *content, int line)
{
	size_t	i;
	char	*new_remain;
	size_t	count;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (!(content[i]))
		return (NULL);
	if (content[i] == '\n')
		line = i++;
	new_remain = malloc(sizeof(char) * ft_strlen(content) - i + 1);
	if (!(new_remain))
		return (NULL);
	count = 0;
	while (content[i])
	{
		new_remain[count++] = content[i];
		i++;
	}
	new_remain[count] = '\0';
	if (line != -1)
		content[line + 1] = '\0';
	return (new_remain);
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
	len = len + find_line(current->content) + 1;
	result = (char *)malloc(len + 1);
    result[0] = '\0';
    current = head;
    while (i + 1 <= len) 
	{
		j = 0;
		while (current->content[j] != '\0' && i + 1 <= len)
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
	pos = find_line(new->content);
	if (pos > 0 || new->content[0] == '\n')
	{
		free(buffer);
		return (-1);
	}
	while (1)
	{
		new->bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (new->bytes_read == 0)
		{
			free(buffer);
			return (-2);
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
	int	check_error;
	
	head = ft_lstnew(remain);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	check_error = read_file(&head, fd);
	if (check_error != 0)
	{
		if (check_error == -1)
		{
			free(remain);
			remain = remain_line(head->content, -1);
			return (head->content);
		}
		ft_free(&head);
		return (NULL);
	}
	next_line = ft_get_line(&head, 0, 0);
	last = ft_lstlast(head);
	free(remain);
	remain = remain_line(last->content, -1);
	ft_free(&head);
	return (next_line);
}
