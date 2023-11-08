#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"

#include <stdio.h>
//#include <libc.h>

static int call = 1;
char	*remain(char *buffer, int pos)
{
	printf("\033[1;33m REMAIN FUNCTION \033[0m\n");
	int i;
	char *remain;
	int	len;
	
	if (!buffer)
		return (NULL);
	printf("\t\t\t\tsó pra testar buffer + pos \033[1;91m %s \033[0m\n", buffer + pos);
	len = ft_strlen(buffer + pos);
	printf("\t\t\t\t saiu len ??? %i\n", len);
	i = 0;
	remain = malloc(sizeof(char) * len + 1);
	if (!remain || len == 0)
	{
		free(remain);
		return (NULL);
	}
	while(buffer[pos + i] != '\0')
	{
		remain[i] = buffer[pos + i];
		i++;
	}
	remain[i] = '\0';
	printf("\033[1;33m LEAVING \033[0m\n");
	return (remain);
}

char *read_line(char *str, int pos)
{
	printf("\033[1;33m READ_LINE FUNCTION \033[0m\n");
	char buffer[pos + 1];
	int	i;

	i = 0;
	if (!str || pos < 0)
		return (NULL);
	while (str[i] != '\n')
	{
		buffer[i] = str[i];
		i++;
	}
	buffer[i++] = '\n';
	buffer[i] = '\0';
	printf("\033[1;33m LEAVING \033[0m\n");
	return (ft_strdup(buffer));
}

int	find_line(char *str)
{
	printf("\033[1;33m FIND_LINE FUNCTION \033[0m\n");
	int	index;
	
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			printf("\033[1;33m LEAVING \033[0m\n");
			return (index);
			break;
		}
		index++;
	}
	printf("\033[1;33m LEAVING \033[0m\n");
	return (-1);
}

char	*get_line(t_list *list)
{
	printf("\033[1;33m GET_LINE FUNCTION \033[0m\n");
	t_list	*ptr;
	ptr = ft_lstlast(list);
	
	printf("\033[1;33m LEAVING \033[0m\n");
	return (ptr->content);
}

t_list *create_node(void)
{
	static t_list	*list;
	printf("\033[1;33m CREATE_NODE FUNCTION \033[0m\n");
	t_list *new;
	t_list *last;

	if (list == NULL)
	{
		list = malloc(sizeof(t_list));
		list->content = ft_strdup("");
		list->bytes_read = -1;
		printf("\t => first node created :");
		printf("contains: |\033[1;34m %s \033[0m|\n", list->content);
		printf("\033[1;33m LEAVING \033[0m\n");
		return list;
	}
	last = ft_lstlast(list);
	if (last->bytes_read == 0)
	{
		printf("\t\t READY TO CLEAN \n");
		clear_list(list);
		return (NULL);
	}
	new = ft_lstnew();
	printf("\t\t => last node acessed\n");
	printf("\t\t ∑∑ byte_readi FROM LAST NODE\033[1;33m %i \033[0m ∑∑ \n", last->bytes_read);
	if (last->remain != NULL || last->bytes_read == -2)
	{
		if (last->bytes_read == 0 && last->content != NULL)
		{
			last->remain = ft_strdup(last->content);
			last->content = NULL;
			return (list);
		}
		new->content = ft_strdup(last->remain);
		printf("\t\t => \033[1;91m remain \33[0m from last call: |\033[1;34m %s \033[0m|\n", last->remain);
		printf("\t\t => update new->content to |\033[1;34m %s \033[0m|\n", new->content);
	}
	if (new->content == NULL)
		new->content = ft_strdup("");
	last->next = new;
	printf("\033[1;33m LEAVING \033[0m\n");
	return (list);
}

char *read_file(t_list **list, int fd)
{
	printf("\033[1;33m READ_FILE FUNCTION \033[0m\n");
	t_list	*new;
	char *buffer;
	int	pos;
	int loops = 1;
	pos = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	new = ft_lstlast(*list);
	printf("\t\t ... Fetch last node ...\n");
	while ((new->bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		printf("\t\t ∑∑ byte_read\033[1;33m %i \033[0m ∑∑ \n", new->bytes_read);
		printf("\t\t ... Loops starts ...\n");
		printf("\t\t => loop @ \033[1;33m %i \033[0m @\n", loops);
		loops++;
		buffer[new->bytes_read] = '\0';
		printf("\t\t => buffer is: |\033[1;34m %s \033[0m|\n", buffer);
		pos = find_line(buffer);
		if (pos >= 0)
		{
			printf("\t\t \033[1;32m√\033[0m FOUND a new line at position | \033[1;33m %i \033[0m |\n", pos);
			printf("\t\t => new->content (old) |\033[1;34m %s \033[0m|\n", new->content);
			new->content = ft_strjoin(new->content, read_line(buffer, pos + 1));
			printf("\t\t => new->content (new) |\033[1;34m %s \033[0m|\n", new->content);
			break;
		}
		printf("\t\t => \033[1;31m X NO\033[0m new line\n");
		printf("\t\t => new->content (old) is |\033[1;34m %s \033[0m|\n", new->content);
		new->content = ft_strjoin(new->content, buffer);
		printf("\t\t => new->content (new) |\033[1;34m %s \033[0m|\n", new->content);
	}
	if (pos != -1 && pos + 1 < new->bytes_read)
		new->remain = remain(buffer, pos + 1);
	printf("\t\t => new->remain \033[1;92m saved \33[0m |\033[1;34m %s \033[0m|\n", new->remain);
	printf("\033[1;33m LEAVING \033[0m\n");
	return (new->content);
}

char	*get_next_line(int fd)
{
	printf("\033[1;33m GET_NEXT_LINE FUNCTION \033[0m\n");
	printf("\t\t // call \033[1;33m %i \033[0m \\\\ \n", call);
	call++;
	t_list	*head = NULL;
	t_list	*last_node;
	static char			*next_line;

	head = create_node(); 
	if (head == NULL)
		return (NULL);
	last_node = ft_lstlast(head);
	printf("\t\t ∑∑ CHEKING BYTES CONDITION \033[1;33m %i \033[0m ∑∑ \n", last_node->bytes_read);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	next_line = read_file(&head, fd);
	printf("\033[1;33m LEAVING READ_FILE \033[0m\n");
	last_node = ft_lstlast(head);
	printf("\033[1;32m  Returning: \033[0m |\033[1;34m %s \033[0m|\n", next_line);
	printf("\033[1;32m  saving: \033[0m |\033[1;34m %s \033[0m|\n", head->remain);
	printf("\033[1;33m LEAVING \033[0m\n");
	return (next_line);
}
