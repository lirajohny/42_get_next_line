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
		if (str[index] == '\n')
		{
			printf("\t\t \033[1;32m√\033[0m FOUND a new line at position | \033[1;33m %i \033[0m \n", index);
			return (index);
			break;
		}
		index++;
	}
			printf("\t\t => \033[1;31m X NO\033[0m new line\n");
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
		return (NULL);
	if (backup[i] == '\n')
		i++;
	rest = malloc(sizeof(char) * ft_strlen(backup) - i + 1);
	if (!(rest))
		return (NULL);
	count = 0;
	while (backup[i])
		rest[count++] = backup[i++];
	rest[count] = '\0';
	return (rest);
}

void ft_free(t_list **list)
{
	printf("\033[1;33m FREE  FUNCTION \033[0m\n");
    t_list *current;
	t_list	*next;

	current = *list;
    while (current != NULL) 
	{
        next = current->next;
		printf("\tADDRESS | \033[1;91m %p \033[0m |  LIBERANDO: |\033[1;36m %s \033[0m| \n", current->content, current->content);
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

	printf(CYAN"\t\t  >>>>  COUNTING LINK LEN <<<< "RESET "\n");
    while (current->next != NULL)
	{
		printf("\tADDRESS | \033[1;91m %p \033[0m | contantdo o tamanho de:  |\033[1;34m %s \033[0m| \n", current->content, current->content);
        len += ft_strlen(current->content);
        current = current->next;
		printf("\t\t\t current LEN = %i\n", len);
    }
	printf("\tADDRESS | \033[1;91m %p \033[0m | por fim contantdo o tamanho de: |\033[1;34m %s \033[0m| \n", current->content, current->content);
	len = len + find_line(current->content);
	printf(CYAN"\t\t  >>>>  GOT LEN <<<< "RESET);
	printf(" %d\n", len);
    
	char *result = (char *)malloc(len + 2);
    result[0] = '\0';

    current = head;
	printf(CYAN "\t\t################## concatenando ##############" RESET "\n");
    while (i < len + 1) 
	{
		printf("\tADDRESS | \033[1;91m %p \033[0m | CONCATENANDO: |\033[1;34m %s \033[0m| \n", current->content, current->content);
		j = 0;
		while (current->content[j] != '\0' && i < len + 1)
		{
			result[i++] = current->content[j++]; 
			printf("result[%i] = %c\n", i - 1, result[i - 1]);
		}
        current = current->next;
    }
	result[i] = '\0';
	printf(CYAN "\t\t################## FIM  ##############" RESET "\n");
	printf("\tADDRESS | \033[1;91m %p \033[0m | RESULT: |\033[1;34m %s \033[0m| \n", result, result);
	printf("\033[1;33m LEAVING \033[0m\n");
    return result;			
}

int	read_file(t_list **list, int fd)
{
	printf("\033[1;33m READ_LINE FUNCTION \033[0m\n");
	t_list	*new;
	char	*buffer;
	int		pos;

	printf("\t head ADDRESS | \033[1;91m %p \033[0m | \033[1;32m\n", list);
	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (1);
	
	new = *list;
	printf(CYAN"\t\t  ~~~~~~ STARTING LOOP ~~~~~~~ "RESET "\n");
	while (1)
	{
		new->bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (new->bytes_read == 0)
			return (1);
		printf("\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", new->bytes_read);
		buffer[new->bytes_read] = '\0';
		printf("\tADDRESS | \033[1;91m %p \033[0m |  BUFFER NOW: |\033[1;34m %s \033[0m| \n", buffer, buffer);
		pos = find_line(buffer);
		if (pos > 0 || buffer[0] == '\n')
		{
			printf(CYAN"\t\t~~~~~~~~  BREAKING LOOP ~~~~~~~~"RESET "\n");
			new->next = ft_lstnew(buffer);
			break;
		}
		new->next = ft_lstnew(buffer);
		new = new->next;
	}
	return (0);
	printf("\033[1;33m LEAVING \033[0m\n");
}

char	*get_next_line(int fd)
{
	printf("\033[1;33m GE_NEXT_LINE FUNCTION \033[0m\n");
	t_list	*head;
	char *next_line;
	static char*	remain;
	t_list	*last;
	static int	check_error;
	
	head = ft_lstnew(remain);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	check_error += read_file(&head, fd);
	if (check_error != 0)
	{
		if (check_error == 1)
		{
			check_error++;
			return (head->content);
		}
		ft_free(&head);
		return (NULL);
	}
	next_line = ft_get_line(&head, 0, 0);
	last = ft_lstlast(head);
	remain = rest_line(last->content);
	ft_free(&head);
	printf("ADDRESS | \033[1;91m %p \033[0m | \033[1;32m leaving phrase  IS: \033[0m |\033[1;34m %s \033[0m| \n", next_line, next_line);
	printf("ADDRESS | \033[1;91m %p \033[0m | \033[1;32m leaving REMAIN IS: \033[0m |\033[1;34m %s \033[0m| \n", remain, remain);
	printf("\033[1;33m LEAVING \033[0m\n");
	return (next_line);
}
