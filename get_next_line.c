/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:55:13 by jlira             #+#    #+#             */
/*   Updated: 2023/11/12 11:44:39 by jlira            ###   ########.fr       */
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
	char	*buff;
	printf("\033[1;33m FETCH LINE FUNCTION \033[0m\n");

	pos = 0;
	printf("\t\033[1;32m  > REMAIN : \033[0m |\033[1;34m %s \033[0m|\n", node->remain);
	if (node->remain != NULL)
		node->line = ft_strdup(node->remain);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (node->bytes_read >= 1)
	{
		printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", node->bytes_read);
		node->bytes_read = read(fd, buff, BUFFER_SIZE);
		buff[node->bytes_read] = '\0';
		pos = find_line(buff);
		if (pos >= 0)
		{
			node->line = ft_strjoin(node->line, ft_substr(buff, 0, pos +1));
			printf("\t\033[1;32m  > LINE : \033[0m |\033[1;34m %s \033[0m|\n", node->line);
			break ;
		}
		node->line = ft_strjoin(node->line, buff);
		printf("\t\033[1;32m  > LINE : \033[0m |\033[1;34m %s \033[0m|\n", node->line);
	}
	if (pos != -1 && pos + 1 < node->bytes_read)
		node->remain = ft_substr(buff, pos +1, ft_strlen(buff));
	free(buff);
	return (node->line);
}

static char	*read_file(int fd, t_list *node)
{
	char	*next_line;

	if (node->remain != NULL)
	{
		node->line = ft_strdup(node->remain);
		printf("\t\033[1;32m  >> juntando line: \033[0m |\033[1;34m %s \033[0m| a : \033[0m |\033[1;34m %s \033[0m|\n", node->remain, node->line);
	}
	next_line = fetch_line(node, fd);
	node->call++;
	return (next_line);
}

char	*get_next_line(int fd)
{
	printf("\033[1;33m GET_NEXT_LINE FUNCTION \033[0m\n");
	char				*next_line;
	static t_list		*node;

	if (node == NULL)
	{
		node = malloc(sizeof(t_list));
		node->call = 1;
		node->line = ft_strdup("");
		node->remain = ft_strdup("");
		node->bytes_read = 2;
	}
	printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", node->bytes_read);
	printf("\t\033[1;32m  > REMAIN INICIO: \033[0m |\033[1;34m %s \033[0m|\n", node->remain);
	printf("\t\033[1;32m  > LINE INICIO: \033[0m |\033[1;34m %s \033[0m|\n", node->line);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	next_line = read_remain(node);
	if (next_line != NULL)
	{
		printf("\033[1;32m  Returning: \033[0m |\033[1;34m %s \033[0m|\n", next_line);
		printf("\033[1;32m  HAS: \033[0m |\033[1;34m %s \033[0m|\n", node->line);
		printf("\033[1;32m  saving: \033[0m |\033[1;34m %s \033[0m|\n", node->remain);
		return (next_line);
	}
	else
	{
		if (node->bytes_read == 0 && node->call != 1)
		{
			return (NULL);
		}
		next_line = read_file(fd, node);
		printf("\033[1;32m  Returning: \033[0m |\033[1;34m %s \033[0m|\n", next_line);
		printf("\033[1;32m  HAS: \033[0m |\033[1;34m %s \033[0m|\n", node->line);
		printf("\033[1;32m  saving: \033[0m |\033[1;34m %s \033[0m|\n", node->remain);
	}
	return (next_line);
}
