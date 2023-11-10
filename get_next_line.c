/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:55:13 by jlira             #+#    #+#             */
/*   Updated: 2023/11/10 14:38:19 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"
//#include <stdio.h>



static char	*check_remain(char *buffer, int pos)
{
	//printf("\033[1;33m CHECK REMAIN FUNCTION \033[0m\n");
	int i;
	char *buff_remain;
	int	len;
	
	if (!buffer)
		return (NULL);
	len = ft_strlen(buffer + pos);
	//printf("\t\t\t\tsó pra testar buffer + pos \033[1;91m %s \033[0m\n", remain + pos);
	i = 0;
	buff_remain = malloc(sizeof(char) * len + 1);
	//printf("\t\t\t\t saiu len ??? %i\n", len);
	if (!buff_remain || len == 0)
		return (NULL);
	while (buffer[pos + i] != '\0')
	{
		buff_remain[i] = buffer[pos + i];
		i++;
	}
	buff_remain[i] = '\0';
	//printf("\033[1;33m LEAVING \033[0m\n");
	return (buff_remain);
}

int	find_line(char *str)
{
	//printf("\033[1;33m FIND_LINE FUNCTION \033[0m\n");
	int	index;
	
	index = 0;
	if (!str)
		return (-1);
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			//printf("\033[1;33m LEAVING \033[0m\n");
			//printf("\t\t \033[1;32m√\033[0m found a new line at position | \033[1;33m %i \033[0m |\n", index);
			return (index);
			break;
		}
		index++;
	}
	//printf("\t\t => \033[1;31m X NO\033[0m new line\n");
	//printf("\033[1;33m LEAVING \033[0m\n");
	return (-1);
}

#include <stdio.h>

static char	*read_remain(char **remain, int *bytes_read, int call)
{
	//printf("\033[1;33m READ REMAIN \033[0m\n");
	char	*buff_remain;
	int pos;

	if ((!remain && call != 1) || (*bytes_read == 0 && call != 1))
	{
		//printf("\t\t \033[1;32m√\033[0m bytes_read | \033[1;33m %i \033[0m |\n", *bytes_read);
		//printf("\t\t \033[1;32m√\033[0m call | \033[1;33m %i \033[0m |\n", call);
		//printf("\033[1;33m NULL REMAIN \033[0m\n");
		return (NULL);
	}
	pos = find_line(*remain);
	if (pos >= 0)
	{
		//printf("\t\t => \033[1;91m remain \33[0m from last call: |\033[1;34m %s \033[0m|\n", *remain);
        buff_remain = ft_substr(*remain, 0, pos + 1);
        if (!buff_remain) 
        {
            free(buff_remain);
            return (NULL);
        } 
		*remain = ft_substr(*remain, pos + 1, ft_strlen(*remain));
		//printf("\t\t => update remain to |\033[1;34m %s \033[0m|\n", *remain);
		//printf("\t\t => RETURNING (BUFF_REMAIN) |\033[1;34m %s \033[0m|\n", buff_remain);
		return (buff_remain);
	}
	//printf("\033[1;33m LEAVING \033[0m\n");
	return (NULL);
}
static char	*read_file(int fd, char **remain, int *i)
{
	//printf("\033[1;33m READ_FILE FUNCTION \033[0m\n");
	char	*buffer;
	int		bytes_read;
	char	*content;
    char    *temp;
	int		pos;
	int loops = 1;

	bytes_read = 0;
	pos = 0;
	bytes_read = 0;
    if (!*remain)
    {
        *remain = ft_strdup("");
        if (!*remain)
        {
            // Handle memory allocation failure
            return (NULL);
        }
    }
    //printf("\033[1;32m BEF >>> : \033[0m |\033[1;34m %s \033[0m|\n", *remain);
	content = ft_strdup(*remain);
	//free(*remain);
    //printf("\033[1;32m  AFF >>> : \033[0m |\033[1;34m %s \033[0m|\n", *remain);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		//printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", bytes_read);
		//printf("\t\t ... Loops starts ...\n");
		//printf("\t\t => loop @ \033[1;33m %i \033[0m @\n", loops);
		loops++;
		buffer[bytes_read] = '\0';
		//printf("\t\t => buffer is: |\033[1;34m %s \033[0m|\n", buffer);
		pos = find_line(buffer);
		if (pos >= 0)
		{
			//printf("\t\t \033[1;32m√\033[0m found a new line at position | \033[1;33m %i \033[0m |\n", pos);
			//printf("\t\t => new->content (old) |\033[1;34m %s \033[0m|\n", content);
            temp = ft_substr(buffer, 0, pos + 1);
			content = ft_strjoin(content, temp);
			//printf("\t\t => new->content (new) |\033[1;34m %s \033[0m|\n", content);
			*i = bytes_read;
			//printf("\t\t ∑∑  UPDATED byte_read\033[1;33m %i \033[0m ∑∑ \n", *i);
            free(temp);
			break ;
		}
		//printf("\t\t => \033[1;31m X NO\033[0m new line\n");
		//printf("\t\t => new->content (old) is |\033[1;34m %s \033[0m|\n", content);
		content = ft_strjoin(content, buffer);
		//printf("\t\t => new->content (new) |\033[1;34m %s \033[0m|\n", content);
	}
    if (pos != -1 && pos + 1 < bytes_read)
		*remain = check_remain(buffer, pos + 1);
	free(buffer);
	//printf("\t\t => new->remain \033[1;92m saved \33[0m |\033[1;34m %s \033[0m|\n", *remain);
	//printf("\033[1;33m LEAVING \033[0m\n");
	*i = bytes_read;
	//printf("\t\t ∑∑  UPDATED byte_read\033[1;33m %i \033[0m ∑∑ \n", *i);
	return (content);
}

char	*get_next_line(int fd)
{
	char	*next_line;
	static char	*remain;
	static int	bytes_read;
	static int call;
	//printf("\033[1;33m GET_NEXT_LINE FUNCTION \033[0m\n");
	//printf("\t\t // call \033[1;33m %i \033[0m \\\\ \n", call);

	if (call == 0)
	{
		call = 1;
		remain = NULL;
		bytes_read = 0;
	}
	//printf("\033[1;32m  REMAIN INICIO: \033[0m |\033[1;34m %s \033[0m|\n", remain);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	
	if ((next_line = read_remain(&remain, &bytes_read, call)) != NULL)
		return (next_line);
	else
	{
		if (bytes_read == 0 && call != 1)
			return (NULL);
		next_line = read_file(fd, &remain, &bytes_read);
	}
	//printf("\033[1;32m  Returning: \033[0m |\033[1;34m %s \033[0m|\n", next_line);
	//printf("\033[1;32m  saving: \033[0m |\033[1;34m %s \033[0m|\n", remain);
	//printf("\033[1;33m LEAVING \033[0m\n");
	//printf("\t\t ∑∑  leaving byte_read\033[1;33m %i \033[0m ∑∑ \n", bytes_read);
	call++;
	return (next_line);
}
