#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
typedef struct s_list
{
	char *content;
	int	bytes_read;
	struct s_list *next;
}	t_list;

char *get_next_line(int fd);
size_t	ft_strlen(char *s);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *content);
void ft_free(t_list **list);
char	*ft_strdup(char *s1);
#endif
