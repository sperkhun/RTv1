/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 18:13:39 by sperkhun          #+#    #+#             */
/*   Updated: 2018/01/09 17:46:00 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_fd			*checkfd(t_fd **des, const int fd)
{
	t_fd	*tmp;
	t_fd	*new;

	if (!*des)
	{
		IFERR2((*des = (t_fd*)malloc(sizeof(t_fd))));
		IFERR2(((*des)->rem = ft_strnew(BUFF_SIZE)));
		(*des)->fd = fd;
		(*des)->next = NULL;
	}
	tmp = (*des);
	while (tmp->fd != fd)
	{
		if (tmp->next)
		{
			tmp = tmp->next;
			continue ;
		}
		IFERR2((new = (t_fd*)malloc(sizeof(t_fd))));
		IFERR2((new->rem = ft_strnew(BUFF_SIZE)));
		new->fd = fd;
		new->next = NULL;
		tmp->next = new;
	}
	return (tmp);
}

static int			readline(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*str;

	while (!ft_strchr(*line, '\n') && (ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (!(str = ft_strjoin(*line, buf)))
			return (-1);
		free(*line);
		*line = str;
	}
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_fd		*des;
	t_fd			*wr;

	if (fd < 0 || !line || read(fd, "", 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	IFERR1((wr = checkfd(&des, fd)));
	IFERR1((*line = ft_strnew(BUFF_SIZE)));
	if (ft_strlen(wr->rem))
	{
		*line = ft_strcpy(*line, wr->rem);
		ft_bzero(wr->rem, ft_strlen(wr->rem));
	}
	if (readline(fd, line) == -1)
		return (-1);
	if (!ft_strlen(*line))
		return (0);
	if (ft_strchr(*line, '\n'))
		wr->rem = ft_strcpy(wr->rem, ft_strchr(*line, '\n') + 1);
	ft_strclr(ft_strchr(*line, '\n'));
	return (1);
}
