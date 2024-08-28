/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:53:44 by bepoisso          #+#    #+#             */
/*   Updated: 2024/08/28 16:43:30 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

void	substract_and_save(char **stash, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	*line = malloc(i + 2);
	if (!*line)
		return (free(*stash));
	ft_strlcpy(*line, *stash, i + 2);
	if ((*stash)[i] == '\n')
		i++;
	temp = ft_strdup(*stash + i);
	if (!temp)
		return (free(*line), free(*stash));
	free(*stash);
	*stash = temp;
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			readed;
	char		*line;
	static char	*stash;
	char		*temp_stash;

	line = NULL;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff || (fd < 0 || BUFFER_SIZE <= 0))
		return (free(buff), free(stash), stash = NULL, NULL);
	if (!stash)
		stash = ft_strdup("");
	while (line == NULL)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1 || (readed == 0 && stash[0] == '\0'))
			return (free(buff), free(stash), stash = NULL, NULL);
		buff[readed] = '\0';
		temp_stash = ft_strjoin(stash, buff);
		free(stash);
		stash = temp_stash;
		if (ft_strchr(stash, '\n') || readed == 0)
			substract_and_save(&stash, &line);
	}
	return (free(buff), line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
// 	char *next_line = "";
// 	int	fd = 0;

// 	fd = open("txt.test", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("FAIL OPEN FILES\n");
// 		return (1);
// 	}
// 	while(1)
// 	{
// 		next_line = get_next_line(fd);
// 		if (!next_line)
// 			break;
// 		printf("%s", next_line);
// 		free(next_line);
// 	}
// 	close(fd);
// 	return (0);
// }
