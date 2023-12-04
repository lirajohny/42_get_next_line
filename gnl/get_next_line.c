/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:58:37 by jlira             #+#    #+#             */
/*   Updated: 2023/12/04 17:45:50 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	find_line(char *str)
{
	int	index;

	index = 0;
	if (str[0] == '\n')
		return (1);
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
			return (index + 1);
		index++;
	}
	return (0);
}

char	*copy_line(struct s_list **list, int len)
{
	t_list	*current;
	char	*result;
	int		i;
	int		j;

	result = (char *)malloc(sizeof(char) * len + 1);
	current = *list;
	i = 0;
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

char	*fetch_line(struct s_list **list)
{
	t_list	*current;
	int		i;
	int		len;

	current = *list;
	len = 0;
	i = 0;
	while (current->next != NULL)
	{
		len += ft_strlen(current->content);
		current = current->next;
	}
	i = find_line(current->content);
	if (i == 0)
		len += ft_strlen(current->content);
	len += i;
	return (copy_line(list, len));
}

char	*read_file(t_list **head, t_list **last, int fd)
{
	char	*buffer;
	t_list	*new;

	new = *last;
	if (new->content[0] == '\n' || find_line(new->content) > 0)
		return (ft_substr(new->content, 0, find_line(new->content)));
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
				*last = new;
				return (fetch_line(head));
			}
			new->next = ft_lstnew(buffer, new->bytes_read, 0);
			new = new->next;
		}
	}
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	t_list		*head;
	char		*next_line;
	static char	*remain;
	t_list		*last;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	head = ft_lstnew(remain, 1);
	last = head;
	next_line = read_file(&head, &last, fd);
	if (next_line == NULL || head == NULL || head->bytes_read <= 0)
	{
		ft_free(&head);
		return (NULL);
	}
	remain = ft_substr(last->content, find_line(last->content), ft_strlen(last->content));
	ft_free(&head);
	return (next_line);
}
