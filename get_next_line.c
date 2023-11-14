#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h>
#include "get_next_line.h"

int	find_line(char *str)
{
	int	index;
	
	index = 0;
	if (str[0] == '\n')
	{
		printf("\t\t \033[1;32m√\033[0m FOUND a new line at position | \033[1;33m %i \033[0m |\n", 0);
		return (0);
	}
	while (str[index] != '\0')
	{
		printf("checking char = | %c | index is %i \n", str[index], index);
		if (str[index] == '\n')
		{
			printf("\t\t \033[1;32m√\033[0m FOUND a new line at position | \033[1;33m %i \033[0m | index is %i\n", index + 1, index);
			return (index + 1);
			break;
		}
		index++;
	}
		printf("\t\t \033[1;32m√\033[0m FOUND a new line at position | \033[1;33m %i \033[0m |\n", index + 1);
	return (0);
}

static char	*rest_line(char *backup)

{
	size_t	i;
	char	*rest;
	size_t	count;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!(backup[i]))
	{
		free(backup);
		return (NULL);
	}
	if (backup[i] == '\n')
		i++;
	rest = malloc(sizeof(char) * ft_strlen(backup) - i + 1);
	if (!(rest))
		return (NULL);
	count = 0;
	while (backup[i])
		rest[count++] = backup[i++];
	rest[count] = '\0';
	free(backup);
	return (rest);
}

char	*check_last(char *last)
{
	printf("\033[1;33m CHECK LAST  FUNCTION \033[0m\n");
	int		len;
	char	*buffer;
	int		i;

	 printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m  LAST IS: \033[0m |\033[1;34m %s \033[0m| \n", last, last);
	if (!last)
		return (NULL);
	i = find_line(last);
	if (i == 0)
	{
		printf("\033[1;33m LEAVING \033[0m\n");
		return(last);
	}	
	printf("PEGANDO LEN DO LAST \n");
	len = ft_strlen(last);
	buffer = malloc(sizeof(char) * (len - i) + 1);
	i = 0;
	while (*last != '\n')
		buffer[i++] = *(last++);
	buffer[i++] = *(last++);
	buffer[i] = '\0';
	 printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m >> UPDATED LAST IS: \033[0m |\033[1;34m %s \033[0m| \n", buffer, buffer);
	printf("\033[1;33m LEAVING \033[0m\n");
	return (buffer);
}

void ft_free(t_list **list)
{
	printf("\033[1;33m FREE  FUNCTION \033[0m\n");
    t_list *current = *list;

    while (current != NULL) 
	{
        t_list *next = current->next;
        free(current->content);
        free(current);
        current = next;
    }
    list = NULL;
	printf("\033[1;33m LEAVING \033[0m\n");
}

char	*ft_get_line(struct s_list **list, int i, int j)
{
	printf("\033[1;33m GET_LINE FUNCTION \033[0m\n");
    t_list	*current;
	t_list	*head = *list;
    int	len = 0;
	

	printf("\t LIST ADDRESS | \033[1;91m %p \033[0m | \033[1;32m\n", list);
	current = head;
	if (list == NULL)
        return NULL;

    while (current->next != NULL)
	{
		printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m contantdo o tamanho de: \033[0m |\033[1;34m %s \033[0m| \n", current->content, current->content);
        len += ft_strlen(current->content);
        current = current->next;
		printf("\t\t\t current LEN = %i\n", len);
    }
	printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m por fim contantdo o tamanho de: \033[0m |\033[1;34m %s \033[0m| \n", current->content, current->content);
	len = len + find_line(current->content);
	printf("\t\t\t TOTAL LEN = %i\n", len);
    
	char *result = (char *)malloc(len + 1);
    result[0] = '\0';

    current = head;
	printf("################## concatenando ##############\n");
    while (i < len) 
	{
		printf("i = %i | j = %i | len = %i |\n", i, j, len);
		printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m CONCATENANDO: \033[0m |\033[1;34m %s \033[0m| \n", current->content, current->content);
		j = 0;
		while (current->content[j] != '\0' && i < len)
		{
			result[i++] = current->content[j++]; 
			printf("result[%i] = %c | current->content[%i] = %c\n", i - 1, result[i - 1], j - 1, current->content[j-1]);
		}
        current = current->next;
    }
	result[i] = '\0';
	printf("################## fim  ##############\n");
	printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m RESULT: \033[0m |\033[1;34m %s \033[0m| \n", result, result);
	printf("\033[1;33m LEAVING \033[0m\n");
    return result;			
}

void	read_file(t_list **list, int fd)
{
	printf("\033[1;33m READ_LINE FUNCTION \033[0m\n");
	t_list	*new;
	char	*buffer;
	int		pos;

	printf("\t head ADDRESS | \033[1;91m %p \033[0m | \033[1;32m\n", list);
	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	
	new = *list;

	while (1)
	{
		new->bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (new->bytes_read == 0)
			return ;
		printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", new->bytes_read);
		buffer[new->bytes_read] = '\0';
		printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m BUFFER NOW: \033[0m |\033[1;34m %s \033[0m| \n", buffer, buffer);
		pos = find_line(buffer);
		if (pos > 0 || buffer[0] == '\n')
		{
			printf("BREAKING THE HABIT\n");
			new->next = ft_lstnew(buffer);
			printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m PTR NOW: \033[0m |\033[1;34m %s \033[0m| \n", new->next->content, new->next->content);
			break;
		}
		new->next = ft_lstnew(buffer);
		printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m PTR NOW: \033[0m |\033[1;34m %s \033[0m| \n", new->next->content, new->next->content);
		new = new->next;
	}
	printf("\033[1;33m LEAVING \033[0m\n");
}

char	*get_next_line(int fd)
{
	t_list	*head;
	char *next_line;
	static char*	remain;
	t_list	*last;
	int pos;
	
	//head = ft_create_list();
	head = ft_lstnew("");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remain != NULL)
 	{	
		next_line = check_last(remain);
 		if (next_line != NULL)
			return (next_line);
		head->content = next_line;
	}
	read_file(&head, fd);
	next_line = ft_get_line(&head, 0, 0);
	last = ft_lstlast(head);
	remain = rest_line(last->content);
	printf("\tADDRESS | \033[1;91m %p \033[0m | \033[1;32m leaving REMAIN IS: \033[0m |\033[1;34m %s \033[0m| \n", remain, remain);
	ft_free(&head);
	printf("\033[1;33m LEAVING \033[0m\n");
	return (next_line);
}
