#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
typedef struct s_list
{
	char *content;
	char *remain;
	int	bytes_read;
	struct s_list *next;
}	t_list;
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char *get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void);
void	clear_list(t_list *head);
#endif
