/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:42:32 by jlira             #+#    #+#             */
/*   Updated: 2023/12/04 17:54:56 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

typedef struct s_list {
  char *content;
  int bytes_read;
  struct s_list *next;
} t_list;

char *get_next_line(int fd);
size_t ft_strlen(char *s);
size_t ft_strlen2(char *s);
t_list *ft_lstlast(t_list *lst);
t_list *ft_lstnew(char *content, int bytes);
char *ft_substr(char *s, unsigned int start, size_t len);
void ft_free(t_list **list);
char *ft_strdup(char *s1);
#endif
