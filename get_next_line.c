#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"

#include <stdio.h>
#include <libc.h>

char	*ft_clear(char *str, char *buffer, int pos)
{
	int i;
	i = 0;
	while(buffer[pos + i] != '\0')
	{
		str[i] = buffer[pos + i];
		i++;
	}
	while(str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
char *read_line(char *str, int pos)
{
	char *input;

	input = ft_substr(str, 0, pos);
	return (input);
}

int	find_line(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			return (index);
			break;
		}
		index++;
	}
	return (-1);
}

t_list read_file(int fd, char *result, t_list *line)
{
	char *buffer;
	int	pos;

	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (1)
	{
		line->bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[line->bytes_read] = '\0';
		if (line->bytes_read <= 0)
		{
			line->bytes_read = -1;
			return (*line);
		}
		pos = find_line(buffer);
		if (pos < 0)
			result = ft_strjoin(result, buffer);
		else
		{
			result = ft_strjoin(result, read_line(buffer, pos + 1));
			break;
		}
	}
	line->line_read = ft_strdup(result);
	line->remain = ft_clear(result, buffer, pos + 1);
	free(buffer);
	return (*line);
}
char	*get_next_line(int fd)
{
	static t_list line;
	if (line.bytes_read == -1)
		return (NULL);
	if (line.remain == NULL)
		line.remain = ft_strdup("");
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

	line = read_file(fd, line.remain, &line);
    if (line.line_read != NULL && line.bytes_read != 0) 
        return (line.line_read);
    return (NULL);
}
