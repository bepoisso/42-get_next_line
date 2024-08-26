/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:43:01 by bepoisso          #+#    #+#             */
/*   Updated: 2024/08/26 15:44:44 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lstsize(lst);
	while (i < size - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
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

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] && (dst_len + i) < (size - 1) && src[i - 1] != '\n')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

int	check_newline(t_list *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while(list->stash[i])
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
		while(list->stash[i])
		{
			count++;
			if (list->stash[i] == '\n')
				return (count);
			i++;
		}
		list = list->next;
	}
	return (count);
}

void	save_buff(char *buff, t_list **list)
{
	t_list	*new;

	new = ft_lstnew(buff);
	if (!new)
		return ;
	if (!*list)
		ft_lstadd_back(list, new);
	else if (!check_newline(*list))
		ft_lstadd_back(list, new);
}

char	*ft_get_line(t_list **list)
{
	char	*dest;
	t_list	*current;

	current = *list;
	dest = malloc(sizeof(char) * (lst_size_char(*list) + 1));
	if (!dest)
		return (NULL);
	while (current)
	{
		ft_strlcat(dest, current->stash, BUFFER_SIZE);
		current = current->next;
	}
	return (dest);
}

t_list *clean_lst(t_list **list)
{
	t_list	*current;
	t_list	*temp;
	int		i;
	int		j;
	char	temp_char[2048];

	i = 0;
	j = 0;
	current = *list;
	while (current->next)
	{
		temp = current->next;
		free(current->stash);
		free(current);
		current = temp;
	}
	while (current->stash[i] != '\n' && current->stash[i])
		i++;
	while (current->stash[i])
		temp_char[j++] = current->stash[i++];
	temp_char[j] = '\0';
	free(current->stash);
	free(current);
	free(temp);
	return (ft_lstnew(temp_char));
}

char	*get_next_line(int fd)
{
	char	*next_line;
	char	*buff;
	int		read_char;
	static t_list	*list;

	read_char = 1;
	buff = malloc(sizeof(char)* BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (read_char)
	{
		read_char = read(fd, buff, BUFFER_SIZE);
		save_buff(buff, &list);
		if (lst_size_char(list) == 0)
		{
			next_line = ft_get_line(&list);
			list = clean_lst(&list);
		}
	}
	return (next_line);
}

#include <stdio.h>
int main()
{
	char *str;
	int fd;

	fd = open("txt.test", O_RDONLY);
	if (fd == -1)
		return (printf("Erreur d'ouvertur du fichier\n"), 1);
	str = get_next_line(fd);
	if (str == NULL)
		return (printf("Erreur de recuperation\n"), 1);
	printf("%s\n", str);
	return (0);
}
