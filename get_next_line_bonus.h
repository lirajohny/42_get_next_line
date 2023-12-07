/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:42:32 by jlira             #+#    #+#             */
/*   Updated: 2023/12/07 12:46:06 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# ifndef MAX_FD
#  define MAX_FD 10
# endif
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	int				bytes;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
size_t	ft_strlen2(char *s);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *content, int bytes, int *i);
char	*ft_substr(char *s, unsigned int start, size_t len, int check);
void	ft_free(t_list **list);
char	*ft_strdup(char *s1);
#endif
