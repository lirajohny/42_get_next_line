/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:55:13 by jlira             #+#    #+#             */
/*   Updated: 2023/11/12 23:13:39 by jlira            ###   ########.fr       */
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
				//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m buff_remain: \033[0m |\033[1;34m %s \033[0m \n", buff_remain, buff_remain);

		node->remain = node->remain + (pos + 1);
				//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  update > node->remain - saving: \033[0m |\033[1;34m %s \033[0m| \n", buff_remain, buff_remain);

			//printf("\033[1;33m LEAVING \033[0m\n");

		return (buff_remain);
	}
	return (NULL);
}

char	*fetch_line(t_list	*node, int fd, int pos)
{
	char	*buff;
		//printf("\033[1;33m FETCH LINE FUNCTION \033[0m\n");


	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	//printf("\t\033[1;32m  > REMAIN : \033[0m |\033[1;34m %s \033[0m|\n", node->remain);

	while (node->bytes_read >= 1)
	{
		node->bytes_read = read(fd, buff, BUFFER_SIZE);
		buff[node->bytes_read] = '\0';
				//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m BUFFER NOW: \033[0m |\033[1;34m %s \033[0m| \n", buff, buff);

		pos = find_line(buff);
		if (pos >= 0)
		{
						//printf("\t\033[1;32m  > LINE : \033[0m |\033[1;34m %s \033[0m|\n", node->line);
			node->line = ft_strjoin(node->line, ft_substr(buff, 0, pos + 1));
					//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m TEMP: \033[0m |\033[1;34m %s \033[0m \n", node->line, node->line);

			break ;
		}
		node->line = ft_strjoin(node->line, buff);
				//printf("\t\033[1;32m  > LINE : \033[0m |\033[1;34m %s \033[0m|\n", node->line);

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
		//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  JUNTANDO BEF> LINE RET: \033[0m |\033[1;34m %s \033[0m| \n", node->line, node->line);
		//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  JUNTANDO BEF> REMAIN RET: \033[0m |\033[1;34m %s \033[0m| \n", node->remain, node->remain);
		node->line = ft_strdup(node->remain);
		//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  JUNTANDO AFF> LINE RET: \033[0m |\033[1;34m %s \033[0m| \n", node->line, node->line);
		//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  JUNTANDO AFF> REMAIN RET: \033[0m |\033[1;34m %s \033[0m| \n", node->remain, node->remain);
		//free(node->remain);
		node->remain = ft_strdup("");
	}
	next_line = fetch_line(node, fd, 0);
	//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  > LINE RET: \033[0m |\033[1;34m %s \033[0m| \n", node->line, node->line);
 	//printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  > REMAIN RET: \033[0m |\033[1;34m %s \033[0m| \n", node->remain, node->remain);
	return (next_line);
}

char	*get_next_line(int fd)
{
		//printf("\033[1;33m GET_NEXT_LINE FUNCTION \033[0m\n");

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
	//printf(" ----------------- previous call ---------------- i\n");
 	//printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", node->bytes_read);
 	//printf("\t\033[1;32m  > REMAIN INICIO: \033[0m |\033[1;34m %s \033[0m|\n", node->remain);
 	//printf("\t\033[1;32m  > LINE INICIO: \033[0m |\033[1;34m %s \033[0m|\n", node->line);
 	//printf("\t ADDRESS | \033[1;91m %p \033[0m | \033[1;32m  > REMAIN INICIO: \033[0m |\033[1;34m %s \033[0m| \n", node->remain, node->remain);
 	//printf("\t ADDRESS | \033[1;91m %p \033[0m | \033[1;32m  > LINE INICIO: \033[0m |\033[1;34m %s \033[0m|  \n", node->line, node->line);
 	//printf(" ----------------- current call ---------------- i\n");
 	//printf("\t\t\t ∑∑ CALL \033[1;33m %i \033[0m ∑∑ \n", node->call);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	remain = read_remain(node);
	if (remain != NULL)
	{
		//printf("\033[1;32m  Returning: \033[0m |\033[1;34m %s \033[0m|\n", next_line);
 		//printf("\033[1;32m  HAS: \033[0m |\033[1;34m %s \033[0m|\n", node->line);
 		//printf("\033[1;32m  saving: \033[0m |\033[1;34m %s \033[0m|\n", node->remain);
		return (remain);
	}
	else
	{
		if (node->bytes_read == 0 && node->call != 1)
			return (NULL);
		next_line = read_file(fd, node);
	}
	//printf("\033[1;32m  Returning: \033[0m |\033[1;34m %s \033[0m|\n", next_line);
 		//printf("\033[1;32m  HAS: \033[0m |\033[1;34m %s \033[0m|\n", node->line);
 		//printf("\033[1;32m  saving: \033[0m |\033[1;34m %s \033[0m|\n", node->remain);
			//printf("\033[1;33m LEAVING \033[0m\n");

	node->call++;
	return (next_line);
}
