/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:58:37 by jlira             #+#    #+#             */
/*   Updated: 2023/12/02 13:16:22 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	return (-1);
}

static char	*remain_line(t_list **last, char *content)
{
	char	*new_remain;
	int		count;
	int		pos;
	int		len;

	if (*content == '\0')
		return (NULL);
	pos = find_line(content) + 1;
	count = 0;
	len = ft_strlen(last, 0, content);
	new_remain = (char *)malloc(sizeof(char) * len - pos + 2);
	if (!(new_remain))
		return (NULL);
	while (content[pos] && pos <= len)
		new_remain[count++] = content[pos++];
	new_remain[count] = '\0';
	return (new_remain);
}

char	*ft_get_line(struct s_list **list, char *last, int i, int j)
{
	t_list	*current;
	char	*result;
	int		len;

	len = ft_strlen(list, 1, last);
	result = (char *)malloc(sizeof(char) * len + 1);
	current = *list;
	while (current != NULL) 
	{
		j = 0;
		while (current->content[j] != '\0' && i < len)
		{
			result[i++] = current->content[j++];
			if (current->content[j - 1] == '\n')
				break ;
		}
		current = current->next;
	}
	result[i] = '\0';
	return (result);
}

int	read_file(t_list **list, int fd)
{
	char	*buffer;
	t_list	*new;

	new = *list;
	if (new->content[0] == '\n' || find_line(new->content) > 0)
		return (-1);
	while (new->bytes_read > 0)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		new->bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[new->bytes_read] = '\0';
		if (new->bytes_read > 0)
		{
			if (find_line(buffer) > 0 || buffer[0] == '\n')
			{
				new->next = ft_lstnew(buffer, new->bytes_read, 0);
				new = new->next;
				*list = new;
				return (0) ;
			}
			new->next = ft_lstnew(buffer, new->bytes_read, 0);
			new = new->next;
		}
	}
	free(buffer);
	return (-2);
}

char	*get_next_line(int fd)
{
	t_list		*head;
	char		*next_line;
	static char	*remain;
	t_list		*last;
	static int	check_error;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd == 1000)
		return (NULL);
	head = ft_lstnew(remain, 1, check_error);
	if (head == NULL)
	{
		ft_free(&head);
		return (NULL);
	}
	last = head;
	check_error = read_file(&last, fd);
	if (head->bytes_read == 0)
	{
		ft_free(&head);
		return (NULL);
	}
	if (check_error == -1)
		next_line = ft_substr(last->content, 0, find_line(last->content) + 1);
	else
		next_line = ft_get_line(&head, last->content, 0, 0);
	remain = remain_line(&last, last->content);
	ft_free(&head);
	return (next_line);
}
