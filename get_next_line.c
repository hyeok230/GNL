/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:49:14 by junylee           #+#    #+#             */
/*   Updated: 2021/05/17 19:04:48 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_nstrlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (*str != '\n' && *str)
	{
		str++;
		len++;
	}
	return (len);
}

int			ft_makeline_sub(t_list *ele, char **line, int *i, size_t *len)
{
	int flag;

	flag = 0;
	while (ele->buf[*i])
	{
		(*line)[(*len)++] = ele->buf[*i];
		if (ele->buf[*i] == '\n')
		{
			(*len)--;
			(*i)++;
			flag = 1;
			break ;
		}
		(*i)++;
	}
	(*line)[*len] = '\0';
	return (flag);
}

int			ft_makeline(t_list *ele, char **line)
{
	size_t	len;
	int		ret;
	int		flag;
	int		i;
	int		j;

	len = ft_strlen(*line);
	if ((ret = ft_addline(line, len, ele)) == -1)
		return (-1);
	i = 0;
	flag = ft_makeline_sub(ele, line, &i, &len);
	j = 0;
	while (ele->buf[i])
		ele->buf[j++] = ele->buf[i++];
	ele->buf[j] = 0;
	return (flag);
}

int			ft_next_line(t_list *ele, int fd, char **line)
{
	int	size;
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if ((ret = ft_makeline(ele, line)) == 1)
		return (ret);
	else if (ret == -1)
		return (ret);
	while ((size = read(fd, ele->buf, BUFFER_SIZE)) > 0)
	{
		ele->buf[size] = 0;
		if ((ret = ft_makeline(ele, line)) == 1)
			return (ret);
		else if (ret == -1)
			return (ret);
	}
	if (size == -1)
		return (-1);
	return (ret);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*head = NULL;
	t_list			*ele;
	int				ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	ele = head;
	while (ele)
	{
		if (ele->fd == fd)
			break ;
		ele = ele->next;
	}
	if (!ele)
	{
		if ((ele = ft_lstnew(fd)) == NULL)
			return (-1);
		ele->next = head;
		head = ele;
	}
	*line = 0;
	ret = ft_next_line(ele, fd, line);
	if (ret == 0 || ret == -1)
		ft_lstdel(&head, fd, ret, line);
	return (ret);
}
