#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int i = 0;
	char *buffer = malloc(sizeof(char) * 10);
	if (!buffer)
	{
		printf("deu ruim\n");
		return (-1);
	}
	buffer = ft_strdup("testando");
	while (buffer[i])
	{
		printf("%c", buffer[i]);
		i++;
	}
	printf("\n -> %s \n", buffer);
	free(buffer);

	int fd;
	int fd_out;
	char *str;

	fd = open("input.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR); 
	if (fd == -1)
	{
		printf("erro while opening input file\n");
		close(fd);
		return (-1);
	}
	fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); 
	if (fd_out == -1)
	{
		printf("erro while opening output file\n");
		close(fd_out);
		return (-1);
	}
	size_t len;
//	write(fd_out, "teste\n", 6);
	int k = 0;
	while((str = get_next_line(fd)) != NULL)
	{
		printf("\n(main.c) escrito:\n%s", str);
		printf("------------------------------------------------------\n");
		len = ft_strlen(str);
		write(fd_out, str, len);
		k++;
	}
free(str);
	close(fd);
	close(fd_out);
}
