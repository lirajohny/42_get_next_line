/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:17:03 by jlira             #+#    #+#             */
/*   Updated: 2023/12/02 10:07:35 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
void	ft_free(t_list **list)
{
	t_list	*current;
	t_list	*next;

	current = *list;
	while (current != NULL)
	{
		next = current->next;
		printf("\t\t => freeing (old) |\033[1;34m %s \033[0m|\n", current->content);
		free(current->content);
		free(current);
		current = next;
	}
	list = NULL;
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (len > size)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_list	*ft_lstnew(char *content, int bytes, int check)
{
	t_list	*new_node;
	char	*new_string;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node || check == -2)
	{
		free(new_node);	
		return (NULL);
	}
	if (content == NULL)
	{
		new_string = ft_strdup("");
		if (!new_string)
			return (NULL);
	}
	else
	{
		new_string = ft_strdup(content);
		if (!new_string)
			return (NULL);
	}
	new_node->content = new_string;
	new_node->bytes_read = bytes;
	new_node->next = NULL;
	free(content);
	return (new_node);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*new_string;
	int		i;

	i = 0;
	new_string = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!new_string)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
