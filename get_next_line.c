/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:18:56 by bjniane           #+#    #+#             */
/*   Updated: 2023/12/06 12:00:12 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(int fd, char *str)
{
	char	*buff;
	ssize_t	i;

	i = 1;
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(str, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[i] = '\0';
		str = ft_strjoin(str, buff);
		if (!str)
			return (NULL);
	}
	free(buff);
	return (str);
}

char	*ft_before(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str[0])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i])
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		line[j++] = str[i++];
	if (str[i] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_next(char *str)
{
	char	*last;
	int		j;
	size_t	i;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	last = malloc(ft_strlen(str) - i + 1);
	if (!last)
		return (NULL);
	if (str[i] == '\n')
		i++;
	while (str[i] != '\0')
		last[j++] = str[i++];
	last[j] = '\0';
	free(str);
	return (last);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*s;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 0x7fffffff)
		return (NULL);
	str = next_line(fd, str);
	if (!str)
		return (NULL);
	s = ft_before(str);
	str = ft_next(str);
	return (s);
}
