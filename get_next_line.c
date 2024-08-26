/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:43:01 by bepoisso          #+#    #+#             */
/*   Updated: 2024/08/26 23:16:10 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->stash = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

int	check_newline(t_list *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->stash[i])
		{
			if (list->stash[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

int	lst_size_char(t_list *list)
{
	int	i;
	int	count;

	count = 0;
	while (list)
	{
		i = 0;
		while (list->stash[i])
		{
			count++;
			if (list->stash[i++] == '\n')
				return (count);
		}
		list = list->next;
	}
	return (count);
}

void	save_buff(char *buff, t_list **list)
{
	t_list	*new;
	char	*content_copy;

	buff[BUFFER_SIZE] = '\0';
	content_copy = ft_strdup(buff);
	if (!content_copy)
		return ;
	new = ft_lstnew(content_copy);
	if (!new)
	{
		free(content_copy);
		return ;
	}
	ft_lstadd_back(list, new);
}

char	*ft_get_line(t_list *list)
{
	char	*line;
	int		i;
	int		j;

	line = malloc(sizeof(char) * (lst_size_char(list) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (list)
	{
		j = 0;
		while (list->stash[j] && list->stash[j] != '\n')
			line[i++] = list->stash[j++];
		if (list->stash[j] == '\n')
		{
			line[i++] = '\n';
			break ;
		}
		list = list->next;
	}
	line[i] = '\0';
	return (line);
}

t_list	*clean_lst(t_list **list)
{
	t_list	*current;
	t_list	*temp;
	int		i;
	char	*temp_char;

	current = *list;
	while (current && current->next)
	{
		temp = current->next;
		free(current->stash);
		free(current);
		current = temp;
	}
	i = 0;
	while (current->stash[i] && current->stash[i] != '\n')
		i++;
	if (current->stash[i] == '\n')
		i++;
	temp_char = ft_strdup(current->stash + i);
	free(current->stash);
	free(current);
	if (temp_char)
		*list = ft_lstnew(temp_char);
	else
		*list = NULL;
	return (*list);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static t_list	*list;
	char		*line;
	int			read_char;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_char = 1;
	while (!check_newline(list) && read_char > 0)
	{
		read_char = read(fd, buff, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(buff);
			while (list)
			{
				t_list *temp = list->next;
				free(list->stash);
				free(list);
				list = temp;
			}
			return (NULL);
		}
		buff[read_char] = '\0';
		save_buff(buff, &list);
	}
	free(buff);
	if (!list)
		return (NULL);
	line = ft_get_line(list);
	list = clean_lst(&list);
	if (!line || (read_char == 0 && !list))
	{
		free(line);
		return (NULL);
	}
	return (line);
}


// #include <stdio.h>
// int main()
// {
// 	char *str;
// 	int fd;

// 	fd = open("txt.test", O_RDONLY);
// 	if (fd == -1)
// 		return (printf("Erreur d'ouvertur du fichier\n"), 1);
// 	while (str)
// 	{
// 		str = get_next_line(fd);
// 		if (str == NULL)
// 			break ;
// 		printf("%s", str);
// 	}
// 	return (0);
// }
