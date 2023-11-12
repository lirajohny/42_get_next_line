/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:55:13 by jlira             #+#    #+#             */
/*   Updated: 2023/11/12 15:33:52 by jlira            ###   ########.fr       */
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
	printf("\033[1;33m READ_REMAIN FUNCTION \033[0m\n");
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
		printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m buff_remain: \033[0m |\033[1;34m %s \033[0m \n", buff_remain, buff_remain);
		node->remain = remain;
		printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  update > node->remain - saving: \033[0m |\033[1;34m %s \033[0m| \n", buff_remain, buff_remain);
	printf("\033[1;33m LEAVING \033[0m\n");
		return (buff_remain);
	}
	return (NULL);
}

char	*fetch_line(t_list	*node, int fd)
{
	printf("\033[1;33m FETCH_LINE FUNCTION \033[0m\n");
	int		pos;
	//char	*buff;
	char	*temp;
	//printf("\033[1;33m FETCH LINE FUNCTION \033[0m\n");

	pos = 0;
	//printf("\t\033[1;32m  > REMAIN : \033[0m |\033[1;34m %s \033[0m|\n", node->remain);
	//buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	char buff[BUFFER_SIZE + 1];
	//if (!buff)
	//	return (NULL);
	while (node->bytes_read >= 1)
	{
		//printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", node->bytes_read);
		node->bytes_read = read(fd, buff, BUFFER_SIZE);
		buff[node->bytes_read] = '\0';
		printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m BUFFER NOW: \033[0m |\033[1;34m %s \033[0m| \n", buff, buff);
		pos = find_line(buff);
		if (pos >= 0)
		{
			int i =0;
			temp = malloc(sizeof(char) * (pos + 2));
			while (buff[i] != '\n')
			{
				temp[i] = buff[i];
				i++;
			}
			temp[i] = '\n';
			temp[i + 1] = '\0';
		printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m TEMP: \033[0m |\033[1;34m %s \033[0m \n", temp, temp);
			node->line = ft_strjoin(node->line, temp);
			free(temp);
			break ;
		}
		node->line = ft_strjoin(node->line, buff);
		//printf("\t\033[1;32m  > LINE : \033[0m |\033[1;34m %s \033[0m|\n", node->line);
	}
	if (pos != -1 && pos + 1 < node->bytes_read)
		node->remain = ft_substr(buff, pos +1, node->bytes_read);
	printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  > update REMAIN: \033[0m |\033[1;34m %s \033[0m | \n", node->remain, node->remain);
//	free(buff);
	printf("\033[1;33m LEAVING \033[0m\n");
	return (node->line);
}

static char	*read_file(int fd, t_list *node)
{
	char	*next_line;
	printf("\033[1;33m READ_FILE FUNCTION \033[0m\n");

	if (node->remain != NULL || node->line == NULL)
		node->line = ft_strdup(node->remain);
	next_line = fetch_line(node, fd);
	node->call++;
	printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  > LINE RET: \033[0m |\033[1;34m %s \033[0m| \n", node->line, node->line);
	printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  > REMAIN RET: \033[0m |\033[1;34m %s \033[0m| \n", node->remain, node->remain);
	printf("\033[1;33m LEAVING \033[0m\n");
	return (next_line);
}

char	*get_next_line(int fd)
{
	printf("\033[1;33m GET_NEXT_LINE FUNCTION \033[0m\n");
	char				*next_line;
	static t_list		*node;
	char				*remain;

	if (node == NULL)
	{
		node = malloc(sizeof(t_list));
		node->call = 1;
		node->line = NULL; 
		node->remain = "";
		node->bytes_read = 2;
	}
	printf(" ----------------- previous call ---------------- i\n");
	printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", node->bytes_read);
	printf("\t ADDRESS | \033[1;91m %p \033[0m | \033[1;32m  > REMAIN INICIO: \033[0m |\033[1;34m %s \033[0m| \n", node->remain, node->remain);
	printf("\t ADDRESS | \033[1;91m %p \033[0m | \033[1;32m  > LINE INICIO: \033[0m |\033[1;34m %s \033[0m|  \n", node->line, node->line);
	printf(" ----------------- current call ---------------- i\n");
	printf("\t\t\t ∑∑ CALL \033[1;33m %i \033[0m ∑∑ \n", node->call);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	remain = read_remain(node);
	if (remain != NULL)
	{
		printf("\033[1;33m LEAVING \033[0m\n");
		return (remain);
	}
	else
	{
		if (node->bytes_read == 0 && node->call != 1)
		{
			return (NULL);
		}
		next_line = read_file(fd, node);
	}
	printf("\033[1;33m LEAVING \033[0m\n");
	node->call++;
	return (next_line);
}
