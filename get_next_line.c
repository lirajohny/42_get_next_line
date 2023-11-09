/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:55:13 by jlira             #+#    #+#             */
/*   Updated: 2023/11/09 13:19:21 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"

static char	*remain(char *buffer, int pos)
{
	int		i;
	char	*remain;
	int		len;

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
	while (buffer[pos + i] != '\0')
	{
		remain[i] = buffer[pos + i];
		i++;
	}
	remain[i] = '\0';
	return (remain);
}

static int	find_line(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			return (index);
			break ;
		}
		index++;
	}
	return (-1);
}
#include <stdio.h>
char	*check_last(t_list *last)
{
	t_list	*new;
	int		len;
	char	*buffer;
	int		i;
	char	*word;

	i = 0;
	len = ft_strlen(last->remain);
	word = last->remain;
	if ((find_line(word) < 0))
		return (NULL);
	buffer = malloc(sizeof(char) * (len - i) + 1);
	i = 0;
	while (*word != '\n')
		buffer[i++] = *(word++);
	buffer[i++] = *(word++);
	buffer[i] = '\0';
	new = ft_lstnew();
	new->content = ft_strdup(buffer);
	new->remain = ft_strdup(word);
	last->next = new;
	free(buffer);
	return (new->content);
}

static t_list	*create_node(int i)
{
	static t_list	*list = NULL;
	t_list			*new;
	t_list			*last;

	if (list == NULL)
	{
		list = malloc(sizeof(t_list));
		list->content = "";
		list->bytes_read = -1;
		return (list);
	}
	last = ft_lstlast(list);
	if (last->bytes_read == 0)
		return (clear_list(&list));
	if (last->remain != NULL && i != 1)
		return (list);
	new = ft_lstnew();
	if (last->remain != NULL)
		new->content = ft_strdup(last->remain);
	else
		new->content = "";
	last->next = new;
	return (list);
}

static char	*read_file(t_list **list, int fd)
{
	t_list	*new;
	char	*buffer;
	int		pos;

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
			new->content = ft_strjoin(new->content, ft_substr(buffer, 0, pos + 1));
			break ;
		}
		new->content = ft_strjoin(new->content, ft_strdup(buffer));
	}
	if (pos != -1 && pos + 1 < new->bytes_read)
		new->remain = remain(buffer, pos + 1);
	free(buffer);
	return (new->content);
}

char	*get_next_line(int fd)
{
	t_list				*head;
	static char			*next_line;
	t_list				*last;

	head = create_node(0);
	last = ft_lstlast(head);
	if (head == NULL)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	if (last->remain != NULL)
	{
		if ((next_line = check_last(last)) != NULL)
			return (next_line);
		head = create_node(1);
	}
	next_line = read_file(&head, fd);
	return (next_line);
}
