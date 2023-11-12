#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
typedef struct s_list
{
	char *line;
	char *remain;
	int	bytes_read;
	int	call;
}	t_list;
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char *get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void);
t_list *clear_list(t_list **head);
#endif
