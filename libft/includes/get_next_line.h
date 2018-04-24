/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:46:06 by sperkhun          #+#    #+#             */
/*   Updated: 2018/01/09 17:48:35 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 1

# define IFERR1(data) if (data == NULL) return (-1);

# define IFERR2(data) if (data == NULL) return (NULL);

typedef struct		s_fd
{
	char			*rem;
	int				fd;
	struct s_fd		*next;
}					t_fd;

int					get_next_line(const int fd, char **line);

#endif
