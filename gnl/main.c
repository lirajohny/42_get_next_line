#include "get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  int fd;
  int fd_out;
  char *str;

  fd = open("2", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
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
