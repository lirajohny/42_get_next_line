/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:55:13 by jlira             #+#    #+#             */
/*   Updated: 2023/11/10 16:17:35 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"
#include <stdio.h>

int	find_line(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (-1);
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

static char	*read_remain(t_list *node)
{
	char	*buff_remain;
	int		pos;
	char	*remain;
	int		bytes_read;

	remain = node->remain;
	bytes_read = node->bytes_read;
	if ((!remain && node->call != 1) || (bytes_read == 0 && node->call != 1))
		return (NULL);
	pos = find_line(node->remain);
	if (pos >= 0)
	{
		buff_remain = ft_substr(node->remain, 0, pos + 1);
		if (!buff_remain)
		{
			free(buff_remain);
			return (NULL);
		}
		remain = ft_substr(remain, pos + 1, ft_strlen(remain));
		node->remain = remain;
		return (buff_remain);
	}
	return (NULL);
}

char	*fetch_line(t_list	*node, int fd)
{
	int		pos;
	char	*content;

	pos = 0;
	content = ft_strdup(node->remain);
	node->buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!node->buf)
		return (NULL);
	while (node->bytes_read > 1)
	{
		node->bytes_read = read(fd, node->buf, BUFFER_SIZE);
		node->buf[node->bytes_read] = '\0';
		pos = find_line(node->buf);
		if (pos >= 0)
		{
			content = ft_strjoin(content, ft_substr(node->buf, 0, pos +1));
			break ;
		}
		content = ft_strjoin(content, node->buf);
	}
	if (pos != -1 && pos + 1 < node->bytes_read)
		node->remain = ft_substr(node->buf, pos +1, ft_strlen(node->buf));
	return (content);
}

static char	*read_file(int fd, t_list *node)
{
	char	*content;

	if (!node->remain)
		node->remain = ft_strdup("");
	content = fetch_line(node, fd);
	node->call++;
	return (content);
}

char	*get_next_line(int fd)
{
	char				*next_line;
	static t_list		*node;

	if (node == NULL)
	{
		node = malloc(sizeof(t_list));
		node->call = 1;
		node->remain = NULL;
		node->bytes_read = 2;
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	next_line = read_remain(node);
	if (next_line != NULL)
		return (next_line);
	else
	{
		if (node->bytes_read == 0 && node->call != 1)
			return (NULL);
		next_line = read_file(fd, node);
	}
	free(node->buf);
	return (next_line);
}

