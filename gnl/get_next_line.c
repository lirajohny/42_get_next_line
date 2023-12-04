/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:58:37 by jlira             #+#    #+#             */
/*   Updated: 2023/12/04 16:49:34 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int find_line(char *str)
{
	int index;

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

char *ft_get_line(struct s_list **list, int i, int j, int len)
{
	t_list *current;
	char *result;

	current = *list;
	while (current->next != NULL)
	{
		len += ft_strlen(current->content);
		current = current->next;
	}
	j = find_line(current->content);
	if (j == 0)
		len += ft_strlen(current->content);
	len += j;
	result = (char *)malloc(sizeof(char) * len + 1);
	current = *list;
	while (current != NULL) {
		j = 0;
		while (current->content[j] != '\0' && i < len)
		{
			result[i++] = current->content[j++];
			if (current->content[j - 1] == '\n')
				break;
		}
		current = current->next;
	}
	result[i] = '\0';
	return (result);
}

int read_file(t_list **list, int fd)
{
	char *buffer;
	t_list *new;

	new = *list;
	if (new->content[0] == '\n' || find_line(new->content) > 0)
		return (-1);
	while (new->bytes_read > 0) {
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		new->bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[new->bytes_read] = '\0';
		if (new->bytes_read > 0) {
			if (find_line(buffer) > 0 || buffer[0] == '\n')
			{
				new->next = ft_lstnew(buffer, new->bytes_read, 0);
				new = new->next;
				*list = new;
				return (0);
			}
			new->next = ft_lstnew(buffer, new->bytes_read, 0);
			new = new->next;
		}
	}
	free(buffer);
	return (-2);
}

char *get_next_line(int fd)
{
	t_list *head;
	char *next_line;
	static char *remain;
	t_list *last;
	static int check_error;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	head = ft_lstnew(remain, 1, 0); // check_error or 0
	last = head;
	if (head != NULL)
		check_error = read_file(&last, fd);
	if (head == NULL || head->bytes_read <= 0)
	{
		ft_free(&head);
		return (NULL);
	}
	if (check_error == -1)
		next_line = ft_substr(last->content, 0, find_line(last->content));
	else
		next_line = ft_get_line(&head, 0, 0, 0);
	remain = ft_substr(last->content, find_line(last->content),
			ft_strlen(last->content));
	ft_free(&head);
	return (next_line);
}
