/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:58:37 by jlira             #+#    #+#             */
/*   Updated: 2023/11/30 12:46:44 by jlira            ###   ########.fr       */
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

static char	*remain_line(char *content)
{
	char	*new_remain;
	int		count;
	int		pos;
	int		len;

	if (content == NULL || *content == '\0')
		return (NULL);
	pos = find_line(content) + 1;
	count = 0;
	len = ft_strlen(content);
	new_remain = (char *)malloc(sizeof(char) * len - pos + 2);
	if (!(new_remain))
		return (NULL);
	while (content[pos] && pos <= len)
		new_remain[count++] = content[pos++];
	new_remain[count] = '\0';
	return (new_remain);
}

char	*ft_get_line(struct s_list **list, int i, int j)
{
	t_list	*current;
	char	*result;
	int		len;

	len = 0;
	current = *list;
	if (current->next->content == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		len += ft_strlen(current->content);
		current = current->next;
	}
	len = len + find_line(current->content);
	result = (char *)malloc(sizeof(char) * len + 2);
	current = *list;
	while (i < len + 1)
	{
		j = 0;
		while (current->content[j] != '\0' && i < len + 1)
			result[i++] = current->content[j++];
		current = current->next;
	}
	result[i] = '\0';
	return (result);
}

int	read_file(t_list **list, int fd)
{
	char	*buffer;
	t_list	*new;
	int		bytes;

	new = *list;
	if (new->content[0] == '\n' || find_line(new->content) > 0)
		return (-1);
	while (1)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (find_line(buffer) > 0 || buffer[0] == '\n')
			break ;
		new->next = ft_lstnew(buffer);
		new = new->next;
	}
	new->next = ft_lstnew(buffer);
	new = new->next;
	*list = new;
	if (bytes <= 0)
		return (-2);
	return (0);
}

char	*get_next_line(int fd)
{
	t_list		*head;
	char		*next_line;
	static char	*remain;
	t_list		*last;
	static int	check;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd == 1000 || check == -2)
		return (NULL);
	head = ft_lstnew(remain);
	last = head;
	check = read_file(&last, fd);
	remain = remain_line(last->content);
	if (remain == NULL || check == -2)
	{
		ft_free(&head);
		free(remain);
		return (NULL);
	}
	if (check == -1)
		next_line = ft_substr(last->content, 0, find_line(last->content) + 1);
	else
		next_line = ft_get_line(&head, 0, 0);
	ft_free(&head);
	printf("\033[1;32m  Returning: \033[0m |\033[1;34m %s \033[0m|\n", next_line);
	printf("\033[1;32m  saving: \033[0m |\033[1;34m %s \033[0m|\n", remain);
	printf("\033[1;33m LEAVING \033[0m\n");
	return (next_line);
}
