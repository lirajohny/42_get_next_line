#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h>
#include "get_next_line.h"

int	find_line(char *str)
{
	//printf("\033[1;33m FIND LINE FUNCTION \033[0m\n");
	int	index;
	
	index = 0;
	if (str[0] == '\n')
	{
		//printf("\t\t \033[1;32m√\033[0m FOUND a new line at position | \033[1;33m %i \033[0m \n", index);
		//printf("\033[1;33m LEAVING  \033[0m\n");
		return (0);
	}
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			//printf("\t\t \033[1;32m√\033[0m FOUND a new line at position | \033[1;33m %i \033[0m \n", index);
			//printf("\033[1;33m LEAVING  \033[0m\n");
			return (index);
		}
		index++;
	}
	//printf("\033[1;33m LEAVING  \033[0m\n");
	return (0);
}

static char	*remain_line(char *content, int line)
{
	//printf("\033[1;33m REMAIN LINE  FUNCTION \033[0m\n");
	size_t	i;
	char	*new_remain;
	size_t	count;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (!(content[i]))
		return (NULL);
	if (content[i] == '\n')
	{
		line = i;
		//printf("\t\t \033[1;32m√\033[0m Still has \\n at | \033[1;33m %i \033[0m \n", line);
		i++;
	}
	new_remain = malloc(sizeof(char) * ft_strlen(content) - i + 1);
	if (!(new_remain))
		return (NULL);
	count = 0;
	while (content[i])
	{
		new_remain[count++] = content[i];
		i++;
	}
	new_remain[count] = '\0';
	if (line != -1)
		content[line + 1] = '\0';
	//printf("ADDRESS | \033[1;91m %p \033[0m | \033[1;32m CONTENT IS after nulling: \033[0m |\033[1;34m %s \033[0m| >> \033[1;34m %c \033[0m\n", content, content, content[line + 1]);
	//printf("\033[1;33m LEAVING  \033[0m\n");
	return (new_remain);
}

char	*ft_get_line(struct s_list **list, int i, int j)
{
	//printf("\033[1;33m GET LINE  FUNCTION \033[0m\n");
	//printf("\t LIST ADDRESS | \033[1;91m %p \033[0m | \033[1;32m\n", list);
    t_list	*current;
	t_list	*head = *list;
	char	*result;
    int	len = 0;
	
	current = head;
	if (list == NULL)
        return NULL;
	//printf(CYAN"\t\t  >>>>  COUNTING LINK LEN <<<< "RESET "\n");
    while (current->next != NULL)
	{
        len += ft_strlen(current->content);
		//printf("\t\t\t current LEN = %i\n", len);
        current = current->next;
    }
	len = len + find_line(current->content) + 1;
	//printf(CYAN"\t\t  >>>>  GOT LEN <<<< "RESET);
	//printf(" %d\n", len);
	result = (char *)malloc(len + 1);
    result[0] = '\0';
    current = head;
	//printf(CYAN "\t\t################## concatenando ##############" RESET "\n");
    while (i + 1 <= len) 
	{
		j = 0;
		while (current->content[j] != '\0' && i + 1 <= len)
		{
			result[i++] = current->content[j++]; 
			//printf("result[%i] = %c\n", i - 1, result[i - 1]);
		}
        current = current->next;
    }
	result[i] = '\0';
	//printf(CYAN "\t\t################## FIM  ##############" RESET "\n");
	//printf("\tADDRESS | \033[1;91m %p \033[0m | RESULT: |\033[1;34m %s \033[0m| \n", result, result);
	//printf("\033[1;33m LEAVING  \033[0m\n");
    return result;			
}

int	read_file(t_list **list, int fd)
{
	//printf("\033[1;33m READ FILE  FUNCTION \033[0m\n");
	t_list	*new;
	char	*buffer;
	int		pos;

	//printf("\t head ADDRESS | \033[1;91m %p \033[0m | \033[1;32m\n", list);
	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (1);
	new = *list;
	pos = find_line(new->content);
	if (pos > 0 || new->content[0] == '\n')
	{
		free(buffer);
		return (-1);
	}
	//printf(CYAN"\t\t  ~~~~~~ STARTING LOOP ~~~~~~~ "RESET "\n");
	while (1)
	{
		new->bytes_read = read(fd, buffer, BUFFER_SIZE);
		//printf("\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", new->bytes_read);
		if (new->bytes_read == 0)
		{
			free(buffer);
			return (-2);
		}
		buffer[new->bytes_read] = '\0';
		//printf("\tADDRESS | \033[1;91m %p \033[0m |  BUFFER NOW: |\033[1;34m %s \033[0m| \n", buffer, buffer);
		pos = find_line(buffer);
		if (pos > 0 || buffer[0] == '\n')
		{
			//printf(CYAN"\t\t~~~~~~~~  BREAKING LOOP ~~~~~~~~"RESET "\n");
			new->next = ft_lstnew(buffer);
			break;
		}
		new->next = ft_lstnew(buffer);
		new = new->next;
	}
	//printf("\033[1;33m LEAVING  \033[0m\n");
	free(buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	//printf("\033[1;33m GET NEXT LINE  FUNCTION \033[0m\n");
	t_list	*head;
	char *next_line;
	static char*	remain;
	t_list	*last;
	int	check_error;
	
	head = ft_lstnew(remain);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	check_error = read_file(&head, fd);
	if (check_error != 0)
	{
		if (check_error == -1)
		{
			free(remain);
			remain = remain_line(head->content, -1);
			//printf("ADDRESS | \033[1;91m %p \033[0m | \033[1;32m leaving REMAIN IS: \033[0m |\033[1;34m %s \033[0m| \n", remain, remain);
			//printf("ADDRESS | \033[1;91m %p \033[0m | \033[1;32m leaving phrase IS: \033[0m |\033[1;34m %s \033[0m| \n", head->content, head->content);
			return (head->content);
		}
		ft_free(&head);
		return (NULL);
	}
	next_line = ft_get_line(&head, 0, 0);
	last = ft_lstlast(head);
	free(remain);
	remain = remain_line(last->content, -1);
	ft_free(&head);
	//printf("ADDRESS | \033[1;91m %p \033[0m | \033[1;32m leaving phrase  IS: \033[0m |\033[1;34m %s \033[0m| \n", next_line, next_line);
	//printf("ADDRESS | \033[1;91m %p \033[0m | \033[1;32m leaving REMAIN IS: \033[0m |\033[1;34m %s \033[0m| \n", remain, remain);
	//printf("\033[1;33m LEAVING  \033[0m\n");
	return (next_line);
}
