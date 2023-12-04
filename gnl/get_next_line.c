/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:58:37 by jlira             #+#    #+#             */
/*   Updated: 2023/12/02 10:09:53 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int find_line(char *str) {
  // printf("\033[1;33m FIND_LINE FUNCTION \033[0m\n");
  int index;

  index = 0;
  if (str[0] == '\n') {
    // printf("\033[1;33m LEAVING FIND_LINE FUNCTION with >> %i
    // <<\033[0m\n",index);
    return (1);
  }
  while (str[index] != '\0') {
    if (str[index] == '\n') {
      // printf("\033[1;33m LEAVING FIND_LINE FUNCTION with >> %i
      // <<\033[0m\n",
      // index);
      return (index + 1);
    }
    index++;
  }
  // printf("\033[1;33m LEAVING FIND_LINE FUNCTION with >> %i <<\033[0m\n",
  // index);
  return (0);
}

/* static char *remain_line(char *content) {
  //printf("\033[1;33m REMAIN_LINE FUNCTION \033[0m\n");
  char *new_remain;
  int count;
  int pos;
  int len;

  if (*content == '\0')
    return (NULL);
  pos = find_line(content) + 1;
  count = 0;
  len = ft_strlen(content);
  new_remain = (char *)malloc(sizeof(char) * len - pos + 2);
  if (!(new_remain))
    return (NULL);
  while (content[pos] && pos <= len)
    new_remain[count++] = content[pos++];
  new_remain[count] = '\0';
  //printf("\033[1;33m LEAVING REMAIN_LINE FUNCTION \033[0m\n");
  return (new_remain);
}*/

char *ft_get_line(struct s_list **list, int i, int j, int len) {
  // printf("\033[1;33m GET_LINE FUNCTION \033[0m\n");
  t_list *current;
  char *result;

  current = *list;
  while (current->next != NULL) {
    len += ft_strlen(current->content);
    current = current->next;
  }
  j = find_line(current->content);
  // printf("\t\t ∑∑ total partial len  \033[1;33m %i \033[0m ∑∑ \n", len);
  if (j == 0)
    len += ft_strlen(current->content);
  len += j;
  // printf("\t\t ∑∑ total len  \033[1;33m %i \033[0m ∑∑ \n", len);
  result = (char *)malloc(sizeof(char) * len + 1);
  current = *list;
  while (current != NULL) {
    // printf("\t\t => current->content |\033[1;34m %s \033[0m| @@ WHEN I IS %i
    // and len is %i \n", current->content, i, len);
    j = 0;
    while (current->content[j] != '\0' && i < len) {
      result[i++] = current->content[j++];
      // printf("\t\t => result[%i] = |\033[1;34m %c \033[0m|\n", i - 1,
      // result[i - 1]);
      if (current->content[j - 1] == '\n')
        break;
    }
    current = current->next;
  }
  // printf("\033[1;33m LEAVING GET_LINE FUNCTION \033[0m\n");
  result[i] = '\0';
  // printf("\t\t => result (old) |\033[1;34m %s \033[0m|\n", result);
  return (result);
}

int read_file(t_list **list, int fd) {

  // printf("\033[1;33m READ_FILE FUNCTION \033[0m\n");
  char *buffer;
  t_list *new;

  new = *list;
  if (new->content[0] == '\n' || find_line(new->content) > 0)
    return (-1);
  while (new->bytes_read > 0) {
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    new->bytes_read = read(fd, buffer, BUFFER_SIZE);
    buffer[new->bytes_read] = '\0';
    // printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", new->bytes_read);
    // printf("\t\t => BUFFER |\033[1;34m %s \033[0m|\n", buffer);
    if (new->bytes_read > 0) {
      if (find_line(buffer) > 0 || buffer[0] == '\n') {
        // printf("\t\t \033[1;32m√\033[0m FOUND a new line at position |
        // "
        //"\033[1;33m :) \033[0m |\n");
        new->next = ft_lstnew(buffer, new->bytes_read, 0);
        new = new->next;
        *list = new;
        ////printf("\033[1;33m LEAVING READ_FILE FUNCTION \033[0m\n");
        return (0);
      }
      // printf("\t\t => \033[1;31m X NO\033[0m new line\n");
      new->next = ft_lstnew(buffer, new->bytes_read, 0);
      new = new->next;
    }
  }
  // printf("\033[1;33m LEAVING READ_FILE FUNCTION \033[0m\n");
  free(buffer);
  return (-2);
}

char *get_next_line(int fd) {
  // printf("\033[1;33m GET_NEXT_LINE FUNCTION \033[0m\n");
  t_list *head;
  char *next_line;
  static char *remain;
  t_list *last;
  static int check_error;

  if (fd < 0 || BUFFER_SIZE <= 0 || fd == 1000)
    return (NULL);
  // printf("\t\t ∑∑ check_error \033[1;33m %i \033[0m ∑∑ \n", check_error);
  head = ft_lstnew(remain, 1, check_error);
  last = head;
  if (head != NULL) {

    ////printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n",
    /// head->bytes_read);
    check_error = read_file(&last, fd);
  }
  if (head == NULL || head->bytes_read <= 0) {
    ft_free(&head);
    return (NULL);
  }
  if (check_error == -1)
    next_line = ft_substr(last->content, 0, find_line(last->content));
  else
    next_line = ft_get_line(&head, 0, 0, 0);
  remain = ft_substr(last->content, find_line(last->content),
                     ft_strlen(last->content));
  ft_free(&head);
  // printf("\033[1;32m  Returning: \033[0m |\033[1;34m %s \033[0m|\n",
  // next_line); printf("\033[1;32m  saving: \033[0m |\033[1;34m %s \033[0m|\n",
  // remain);
  // printf("\033[1;33m LEAVING \033[0m\n");
  return (next_line);
}
