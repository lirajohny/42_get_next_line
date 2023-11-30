#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>
/*
int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Uso: %s <conteudo_do_arquivo>\n", argv[0]);
		return 1;
	}

	char *conteudo_do_arquivo = argv[1];
	int fd = open("arquivo_saida.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("Erro ao criar o arquivo");
		return 1;
	}
	printf("fd is : %i <\n", fd);
	ssize_t bytes_escritos = write(fd, conteudo_do_arquivo, strlen(conteudo_do_arquivo));
	if (bytes_escritos == -1) {
		perror("Erro ao escrever no arquivo");
		close(fd);
		return 1;
	}
	lseek(fd, 0, SEEK_SET);
	char *line = get_next_line(fd);
	printf("returned: %s <\n", line);
	if (strcmp(line, conteudo_do_arquivo) == 0)
		printf("\033[1;32m OK \033[0m\n");
	else 
		printf("\033[1;31m KO \033[0m\n");
	free(line);
	close(fd);

	return 0;
}

int   main(int ac, char **av)
{
	char  *line;
	int   fd;

	const char *str = av[1];
	(void)ac;
	printf("av[1] is : %s <\n", str);
	fd = open(str, O_RDWR); 
	printf("fd is : %i <\n", fd);
	if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        fprintf(stderr, "errno = %d\n", errno);
        return 1;
    }
	line = get_next_line(fd);
	printf("returned: %s <\n", line);
	if (strcmp(line, str) == 0)
		printf("\033[1;32m OK \033[0m\n");
	else 
		printf("\033[1;31m KO \033[0m\n");
	free(line);
	close(fd);
	return (0);
}*/


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
		if (i == 83)
			break ;
		free(str);
	}
	printf("\n- LEAVING (main.c)  got: >> %s <<\n",str);
	free(str);
	close(fd);
	close(fd_out);
    return (0);
}

