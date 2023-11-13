/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:55:13 by jlira             #+#    #+#             */
/*   Updated: 2023/11/12 23:20:42 by jlira            ###   ########.fr       */
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
	int		bytes_read;

	bytes_read = node->bytes_read;
	if ((!node->remain && node->call != 1) || (bytes_read == 0 && node->call != 1))
	{
		free(node->remain);
		return (NULL);
	}
	pos = find_line(node->remain);
	if (pos >= 0)
	{
		buff_remain = ft_substr(node->remain, 0, pos + 1);
		node->remain = node->remain + (pos + 1);
		return (buff_remain);
	}
	return (NULL);
}

char	*fetch_line(t_list	*node, int fd, int pos)
{
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (node->bytes_read >= 1)
	{
		node->bytes_read = read(fd, buff, BUFFER_SIZE);
		buff[node->bytes_read] = '\0';
		pos = find_line(buff);
		if (pos >= 0)
		{
			node->line = ft_strjoin(node->line, ft_substr(buff, 0, pos + 1));
			break ;
		}
		node->line = ft_strjoin(node->line, buff);
	}
	if (pos != -1 && pos + 1 < node->bytes_read)
		node->remain = ft_substr(buff, pos + 1, ft_strlen(buff));
	free(buff);
	return (node->line);
}

static char	*read_file(int fd, t_list *node)
{
	char	*next_line;

	if (node->remain != NULL)
	{
		node->line = ft_strdup(node->remain);
		//free(node->remain);
		node->remain = ft_strdup("");
	}
	next_line = fetch_line(node, fd, 0);
	return (next_line);
}

char	*get_next_line(int fd)
{
	char				*next_line;
	static t_list		*node;
	char				*remain;

	if (node == NULL)
	{
		node = malloc(sizeof(t_list));
		node->call = 1;
		node->line = ft_strdup("");
		node->remain = ft_strdup("");
		node->bytes_read = 2;
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	remain = read_remain(node);
	if (remain != NULL)
		return (remain);
	else
	{
		if (node->bytes_read == 0 && node->call != 1)
			return (NULL);
		next_line = read_file(fd, node);
	}
	node->call++;
	return (next_line);
}
