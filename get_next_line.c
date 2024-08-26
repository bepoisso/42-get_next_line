/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:43:01 by bepoisso          #+#    #+#             */
/*   Updated: 2024/08/26 02:14:15 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	file_count_line(int fd)
{
	int			count;
	static int	size;
	char 		buff[1];

	size = 1;
	count = 0;
	while (buff[0] != '\n')
	{
		size = read(fd, buff, 1);
		count++;
		if (size == -1)
			return (0);
	}
	return (count);
}

char	*get_next_line(int fd)
{
	char	*dest;
	int		i;
	char	buff[1];
	int		size;

	i = 0;
	size = file_count_line(fd);
	if (size == -1)
		return (NULL);
	dest = malloc(sizeof(char) * size + 1);
	while (*buff != '\n')
	{
		size = read(fd, buff, 1);
		dest[i] = *buff;
		i++; 
	}
	dest[i] = '\0';
	return (dest);
}
