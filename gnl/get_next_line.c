/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:58:37 by jlira             #+#    #+#             */
/*   Updated: 2023/12/02 10:09:53 by jlira            ###   ########.fr       */
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

	if (*content == '\0')
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
	while (current->next != NULL)
	{
		len += ft_strlen(current->content);
		current = current->next;
	}
	//printf("\t\t ∑∑ total partial len  \033[1;33m %i \033[0m ∑∑ \n", len);
	if (find_line(current->content) != -1)
		len = len + find_line(current->content) + 1;
	else
		len = len + ft_strlen(current->content);
	//printf("\t\t ∑∑ total len  \033[1;33m %i \033[0m ∑∑ \n", len);
	result = (char *)malloc(sizeof(char) * len + 1);
	current = *list;
	while (current != NULL) 
	{
					//printf("\t\t => current->content (old) |\033[1;34m %s \033[0m|\n", current->content);
		j = 0;
		while (current->content[j] != '\0' && i < len)
		{
			result[i++] = current->content[j++];
			//printf("\t\t => result[%i] = |\033[1;34m %c \033[0m|\n",i - 1, result[i - 1]);
			if (current->content[j - 1] == '\n')
				break ;
		}
		current = current->next;
	}
	result[i] = '\0';
				//printf("\t\t => result (old) |\033[1;34m %s \033[0m|\n", result);
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
//	printf("\t\t ∑∑ check  \033[1;33m %i \033[0m ∑∑ \n", check_error);
	head = ft_lstnew(remain, 1, check_error);
	if (head == NULL)
	{
		//printf("here\n");
		ft_free(&head);
		return (NULL);
	}
	last = head;
	check_error = read_file(&last, fd);
	//printf("\t\t\t\t\t check error >>>> %i \n", check_error);
	if (check_error == -1)
		next_line = ft_substr(last->content, 0, find_line(last->content) + 1);
	else
		next_line = ft_get_line(&head, 0, 0);
	remain = remain_line(last->content);
	ft_free(&head);
	return (next_line);
}
