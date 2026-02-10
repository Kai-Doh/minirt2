/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:22:51 by ktiomico          #+#    #+#             */
/*   Updated: 2024/11/19 00:07:30 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_line(int fd, char *buffer, char *stock)
{
	int		read_count;
	char	*tmp;

	read_count = 1;
	while (read_count > 0)
	{
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (read_count == -1)
		{
			free (stock);
			return (NULL);
		}
		else if (read_count == 0)
			return (stock);
		buffer[read_count] = 0;
		if (!stock)
			stock = ft_strdup("");
		tmp = stock;
		stock = ft_strjoin(tmp, buffer);
		free (tmp);
		if (ft_strchr(buffer, '\n'))
			return (stock);
	}
	return (stock);
}

static char	*find_line(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (!line[i])
		return (NULL);
	tmp = ft_substr(line, i + 1, ft_strlen(line));
	if (!*tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	line[i + 1] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free (stock);
		stock = NULL;
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer, stock);
	free (buffer);
	if (!line)
		return (NULL);
	stock = find_line(line);
	return (line);
}
