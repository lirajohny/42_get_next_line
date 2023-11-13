#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int fd;
	int fd_out;
	char *str;

	fd = open("input2.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR); 
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
	//printf("MAIN\n");
	while((str = get_next_line(fd)) != NULL)
	{
		//printf("\n- END - (main.c) escrito: %s\n", str);
		//printf("------------------------------------------------------\n");
		len = ft_strlen(str);
		write(fd_out, str, len);
		free(str);
	}
	//printf("\033[1;32m MAIN GOT: \033[0m |\033[1;34m %s \033[0m| ... LEAVING ... \n", str);
	//free(str);
	free(str);
	close(fd);
	close(fd_out);
    return (0);
}
