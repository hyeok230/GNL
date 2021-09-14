/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:28:08 by junylee           #+#    #+#             */
/*   Updated: 2021/05/17 18:54:49 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t		ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (*str++)
	{
		len++;
	}
	return (len);
}

t_list		*ft_lstnew(int fd)
{
	t_list	*ret;

	if (!(ret = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	ret->fd = fd;
	ret->next = NULL;
	ret->buf[0] = 0;
	return (ret);
}

t_list		*ft_find(t_list **head, int fd)
{
	t_list	*ret;

	ret = *head;
	while (ret)
	{
		if (ret->fd == fd)
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

void		ft_lstdel(t_list **head, int fd, int ret, char **line)
{
	t_list	*pre;
	t_list	*cur;

	if (ret == -1)
	{
		free(*line);
		*line = 0;
	}
	pre = *head;
	if (pre->fd == fd)
	{
		*head = pre->next;
		free(pre);
		return ;
	}
	while (pre->next->fd != fd)
		pre = pre->next;
	cur = ft_find(head, fd);
	pre->next = cur->next;
	free(cur);
	return ;
}

int			ft_addline(char **line, size_t len, t_list *ele)
{
	char		*new;
	size_t		i;

	i = ft_nstrlen(ele->buf);
	if (!(new = (char*)malloc(sizeof(char) * (len + i + 1))))
		return (-1);
	i = 0;
	while (i < len)
	{
		new[i] = (*line)[i];
		i++;
	}
	new[i] = '\0';
	free(*line);
	*line = new;
	return (1);
}
