/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:58:37 by jlira             #+#    #+#             */
/*   Updated: 2023/12/07 06:21:36 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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
//	printf("\033[1;32m  Result: \033[0m |\033[1;34m %s \033[0m|\n", result);
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

#include <stdio.h>
/*
char	*read_file(t_list **head, t_list **last, int fd, int check)
{
	char	*buffer;

	printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", (*last)->bytes_read);
	if (find_line((*last)->content) > 0)
		return (ft_substr((*last)->content, 0, find_line((*last)->content)));
	while ((*last)->bytes_read > 0)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		(*last)->bytes_read = read(fd, buffer, BUFFER_SIZE);
		printf("\t\t ∑∑ now byte_read\033[1;33m %i \033[0m ∑∑ \n", (*last)->bytes_read);
		if ((*last)->bytes_read > 0)
		{
			buffer[(*last)->bytes_read] = '\0';
			printf("buffer is %s\n", buffer);
			check++;
			if (find_line(buffer) > 0)
				break ;
			(*last)->next = ft_lstnew(buffer, (*last)->bytes_read);
			*last = (*last)->next;
		}
	}
	if (check != 0)
	{
		(*last)->next = ft_lstnew(buffer, (*last)->bytes_read);
		*last = (*last)->next;
		return (fetch_line(head));
	}
	free(buffer);
	return (NULL);
}
*/
char	*read_file(t_list **head, t_list **last, int fd, char *remain)
{
	char	*buffer;
	int		readtime = 0;
//	printf("read file --\n");
	if (find_line((*last)->content) > 0)
	{
//		printf("entreeein--\n");
		return (ft_substr((*last)->content, 0, find_line((*last)->content), 0));
	}
	while ((*last)->bytes_read > 0)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		(*last)->bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[(*last)->bytes_read] = '\0';
		if ((*last)->bytes_read > 0 || remain != NULL || ((*last)->bytes_read == 0 && readtime > 0))
		{
			if (find_line(buffer) > 0 || remain != NULL || ((*last)->bytes_read == 0 && readtime > 0))
			{
				(*last)->next = ft_lstnew(buffer, (*last)->bytes_read);
				*last = (*last)->next;
				return (fetch_line(head));
			}
			(*last)->next = ft_lstnew(buffer, (*last)->bytes_read);
			readtime++;
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
	static char	*remain;
	t_list		*last;
	int			pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	head = ft_lstnew(remain, 1);
	last = head;
	next_line = read_file(&head, &last, fd, remain);
	if (next_line == NULL && head->content == NULL && head->bytes_read <= 0)
	{
		ft_free(&head);
		return (NULL);
	}
	pos = find_line(last->content);
	remain = ft_substr(last->content, pos,
			ft_strlen(last->content + pos), 1);
	ft_free(&head);
//	printf("\033[1;32m  Returning: \033[0m |\033[1;34m %s \033[0m|\n", next_line);
 //	printf("\033[1;32m  saving: \033[0m |\033[1;34m %s \033[0m|\n", remain);
	return (next_line);
}
