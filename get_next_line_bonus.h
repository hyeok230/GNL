/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:25:36 by junylee           #+#    #+#             */
/*   Updated: 2021/05/17 19:09:02 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	int					fd;
	char				buf[BUFFER_SIZE + 1];
	struct s_list		*next;
}					t_list;
int					ft_makeline(t_list *ele, char **line);
int					ft_makeline_sub(t_list *ele, char **line,
		int *i, size_t *len);
int					ft_next_line(t_list *ele, int fd, char **line);
int					get_next_line(int fd, char **line);
size_t				ft_strlen(char *str);
size_t				ft_nstrlen(char *str);
t_list				*ft_lstnew(int fd);
t_list				*ft_find(t_list **head, int fd);
void				ft_lstdel(t_list **head, int fd, int ret, char **line);
int					ft_addline(char **line, size_t len, t_list *ele);
int					get_next_line(int fd, char **line);

#endif
