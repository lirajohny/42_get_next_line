#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"


/*
int   main(int ac, char **av)
{
  char  *line;
  int   fd1;
  //int   fd2;

  (void)ac;
  (void)av;
  fd1 = open("input", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
  //fd2 = open(av[2], O_RDONLY);
  while ((line = get_next_line(fd1)) != NULL) 
  {
	printf("returned: %s <\n", line);
	free(line);
  }
  line = get_next_line(fd1);
  printf("returned: %s <\n", line);
  //free(line);
  close(fd1);
  return (0);
}
*/
int	main(void)
{
	int fd;
	int fd_out;
	char *str;

	fd = open("output", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR); 
	if (fd == -1)
	{
		//printf("erro while opening input file\n");
		close(fd);
		return (-1);
	}
	fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); 
	if (fd_out == -1)
	{
		//printf("erro while opening output file\n");
		close(fd_out);
		return (-1);
	}
	size_t len;
	int i = 1; 
	while((str = get_next_line(fd)) != NULL)
	{
		printf("\n- END - (main.c) [%i] escrito: >> %s <<\n",i,str);
		printf("------------------------------------------------------\n");
		i++;
		len = ft_strlen(str);
		write(fd_out, str, len);
		free(str);
	}
	printf("\n- LEAVING (main.c)  got: >> %s <<\n",str);
	free(str);
	close(fd);
	close(fd_out);
    return (0);
}
