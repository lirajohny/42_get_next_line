#include "get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av) {
  int fd;
  int fd_out;
  char *str;

  if (ac < 2) {
	  fprintf(stderr, "Uso: %s <conteudo_do_arquivo>\n", av[0]);
	  return 1;
  }

  char *file_open = av[1];
  fd = open(file_open, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    // printf("erro while opening input file\n");
    close(fd);
    return (-1);
  }
  fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd_out == -1) {
    // printf("erro while opening output file\n");
    close(fd_out);
    return (-1);
  }
  size_t len;
  int i = 1;
  while ((str = get_next_line(fd)) != NULL) {
    printf("\n- END - (main.c) [%i] escrito: >> %s <<\n", i, str);
    printf("------------------------------------------------------\n");
    i++;
    len = ft_strlen(str);
    write(fd_out, str, len);
    if (i == 83)
      break;
    free(str);
  }
  printf("\n- LEAVING (main.c)  got: >> %s <<\n", str);
  free(str);
  close(fd);
  close(fd_out);
  return (0);
}
