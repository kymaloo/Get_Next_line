/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:18:23 by trgaspar          #+#    #+#             */
/*   Updated: 2023/11/18 21:45:47 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char	*ft_line_right(int	fd, char *buff)
{
	int		rd_bytes;
	char	*str;

	rd_bytes = 1;
	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (!ft_strchr(str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (NULL);
		buff[rd_bytes] = '\0';
		str = ft_strjoin(str, buff);
		if (!str)
			return (NULL);
	}
	return (str);
}


char *get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	char	*str;

	str = ft_line_right(fd, buff);
	return (str);
}

#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("test", O_RDONLY);
	if (fd == -1)
		return (1);
	while (i < 3)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
}
