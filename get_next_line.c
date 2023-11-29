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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_line_right(int fd, char *buff)
{
	int		rd_bytes;
	char	*str;

	rd_bytes = 1;
	if (buff)
		str = malloc(ft_strlen(buff) * sizeof(char) + 1);
	else
		str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	ft_strlcat(str, buff, ft_strlen(buff) + 1);
	if (!str)
		return (NULL);
	while (!ft_strchr(str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (buff[0] = '\0', free(str), NULL);
		buff[rd_bytes] = '\0';
		str = ft_strjoin(str, buff);
		if (!str || ft_strlen(str) == 0)
			return (free(str), NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	char		*str;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = ft_line_right(fd, buff);
	if (!tmp)
		return (NULL);
	str = ft_get_line(tmp);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	tmp = ft_get_new_line(tmp);
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	buff[0] = '\0';
	ft_strlcat(buff, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (str);
}
