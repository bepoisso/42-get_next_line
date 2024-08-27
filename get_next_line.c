/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:53:44 by bepoisso          #+#    #+#             */
/*   Updated: 2024/08/27 19:00:10 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	substract_and_save(char **stash, char **line)
{
	int	i;
	int	j;
	char *temp;

	j = 0;
	i = 0;
	temp = malloc(ft_strlen(*stash) + 1);
	*line = malloc(ft_strlen(*stash) + 1);
	if (!*line || !temp)
		return ;
	while ((*stash)[i] != '\n')
	{
		(*line)[i] = (*stash)[i];
		i++;
	}
	(*line)[i] = '\n';
	(*line)[++i] = '\0';
	while ((*stash)[i])
	{
		temp[j] = (*stash)[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	*stash = temp;
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			readed;
	char		*line;
	static char	*stash;

	readed = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!stash)
		stash = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE <= 0 || !buff || !stash)
		return (NULL);
	while (readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		//On cherche si on trouve un '/n' dans buff
		if (ft_strchr(buff, '\n') != NULL)
		{
			//on ajoute le contenu de buff dans stash
			//on mets stash dans line
			//on mets le reste apres '/n' dans stash
			stash = ft_strjoin(stash, buff);
			substract_and_save(&stash, &line);
			return (line);
		}
		else
		{
			//on ajoute le contenue de buff dans stash
			stash = ft_strjoin(stash, buff);
		}
	}
	return (NULL);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	char *next_line = "";
// 	int	fd = 0;
// 	int i = 0;

// 	fd = open("txt.test", O_RDONLY);
// 	if (fd < 0)
// 		printf("FAIL OPEN FILES\n");
// 	while(1)
// 	{
// 		next_line = get_next_line(fd);
// 		if (!next_line)
// 			return (0);
// 		printf("%s", next_line);
// 		i++;
// 	}
// 	return (0);
// }
