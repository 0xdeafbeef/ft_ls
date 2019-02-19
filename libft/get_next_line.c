/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 16:26:55 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/16 19:18:45 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	line_magic(char **line, char **stor)
{
	char *item;

	if ((item = ft_strchr(*stor, '\n')))
	{
		item[0] = '\0';
		*line = ft_strdup(*stor);
		item = ft_strdup(&item[1]);
		free(*stor);
		*stor = item;
		return (1);
	}
	*line = ft_strdup(*stor);
	ft_strdel(stor);
	return (1);
}

int			readler(char buf[BUFF_SIZE], char **stor, ssize_t bytes_red)
{
	int		flag;
	char	*temp;

	flag = !ft_strchr(buf, '\n') ? 0 : 1;
	buf[bytes_red] = 0x0;
	temp = !(*stor) ? ft_strdup(buf) : ft_strjoin(*stor, buf);
	free(*stor);
	*stor = temp;
	return (flag);
}

int			get_next_line(const int fd, char **line)
{
	ssize_t		bytes_red;
	char		buf[BUFF_SIZE + 1];
	static char	*stor[MAX_UNIX_KERNEL_FD_COUNT];

	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (!stor[fd])
		stor[fd] = ft_strnew(0);
	bytes_red = 0;
	if (ft_strchr(stor[fd], '\n') == 0x0)
		while ((bytes_red = read(fd, buf, BUFF_SIZE)))
		{
			if (readler(buf, &stor[fd], bytes_red))
				break ;
		}
	if (!*stor[fd] && !bytes_red)
	{
		ft_strdel(&stor[fd]);
		return (0);
	}
	return (line_magic(line, &stor[fd]));
}
