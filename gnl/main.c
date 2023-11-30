#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>

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
