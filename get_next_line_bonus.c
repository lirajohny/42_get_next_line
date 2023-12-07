/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:58:37 by jlira             #+#    #+#             */
/*   Updated: 2023/12/07 12:39:17 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	get_line(char *str)
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
		len += BUFFER_SIZE; 
		current = current->next;
	}
	i = get_line(current->content);
	if (i == 0)
		len += ft_strlen(current->content);
	len += i;
	return (copy_line(list, len));
}

char	*read_file(t_list **head, t_list **last, int fd, char *rest)
{
	char	*buffer;
	int		i;

	i = 0;
	if (get_line((*last)->content) > 0)
		return (ft_substr((*last)->content, 0, get_line((*last)->content), 0));
	while ((*last)->bytes > 0)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		(*last)->bytes = read(fd, buffer, BUFFER_SIZE);
		if ((*last)->bytes > 0 || rest || ((*last)->bytes == 0 && i > 0))
		{
			buffer[(*last)->bytes] = '\0';
			if (get_line(buffer) > 0 || rest || ((*last)->bytes == 0 && i > 0))
			{
				(*last)->next = ft_lstnew(buffer, (*last)->bytes, &i);
				*last = (*last)->next;
				return (fetch_line(head));
			}
			(*last)->next = ft_lstnew(buffer, (*last)->bytes, &i);
			*last = (*last)->next;
		}
	}
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	t_list		*head;
	char		*next_line;
	static char	*rest[MAX_FD];
	t_list		*last;
	int			pos;

	pos = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	head = ft_lstnew(rest[fd], 1, &pos);
	last = head;
	next_line = read_file(&head, &last, fd, rest[fd]);
	if (next_line == NULL && head->content == NULL && head->bytes <= 0)
	{
		ft_free(&head);
		return (NULL);
	}
	pos = get_line(last->content);
	rest[fd] = ft_substr(last->content, pos,
			ft_strlen(last->content + pos), 1);
	ft_free(&head);
	return (next_line);
}
