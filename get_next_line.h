/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:44:33 by bepoisso          #+#    #+#             */
/*   Updated: 2024/08/26 22:36:55 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*stash;
	struct s_list	*next;
	
}	t_list;

char	*get_next_line(int fd);
t_list *clean_lst(t_list **list);
void	save_buff(char *buff, t_list **list);
int	lst_size_char(t_list *list);
int	check_newline(t_list *list);
int	ft_strlcat(char *dst, const char *src, int size);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int	ft_lstsize(t_list *lst);
char	*ft_strdup(const char *s);
int	ft_strlen(const char *s);
char	*ft_get_line(t_list *list);

#endif
