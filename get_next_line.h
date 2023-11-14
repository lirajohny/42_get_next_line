#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"


#include <stdlib.h>
#include <unistd.h>
typedef struct s_list
{
	char *content;
	int	bytes_read;
	struct s_list *next;
}	t_list;
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif
char	*ft_strjoin(char *s1, char *s2);
char *get_next_line(int fd);
size_t	ft_strlen(char *s);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *content);
void	clear_list(t_list *head);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
#endif
