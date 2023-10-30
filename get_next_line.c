#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"

char *get_next_line(int fd)
{
	char str_buffer[1024];
	int	ret;
    size_t len;
    char c;
    char *input;
   
	ret = 0;
	len = 0;
    while (1)
    {
		ret = read(fd, &c, 1);
		if (ret <= 0)
			return (NULL);
        if (c == '\n')
        {
			str_buffer[len++] = '\n';
			break;
        }
        str_buffer[len++] = c;
    }
    str_buffer[len] = '\0'; 
    input = ft_strdup(str_buffer);
    if (!input)
        return (NULL);
    return input;
}
