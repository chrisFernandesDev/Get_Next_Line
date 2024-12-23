/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaciel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:53:42 by cmaciel-          #+#    #+#             */
/*   Updated: 2024/12/20 10:53:42 by cmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_find_line(int fd, char *buffer)
{
	char	*line_tmp;
	char	*line_res;
	ssize_t	byte_read;

	line_tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line_tmp)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0 && ft_find_newline(buffer) == 0)
	{
		byte_read = read(fd, line_tmp, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(line_tmp), free(buffer), NULL);
		line_tmp[byte_read] = '\0';
		line_res = ft_strjoin(buffer, line_tmp);
		if (!line_res)
			return (free(line_tmp), free(buffer), NULL);
		free(buffer);
		buffer = line_res;
	}
	free(line_tmp);
	return (buffer);
}

char	*ft_extract_line(char *buffer)
{
	char	*new_line;
	int		i;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	new_line = (char *)ft_calloc(i + 2, sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		new_line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

char	*ft_read_line(char *buffer)
{
	char	*remainder;
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	remainder = (char *)ft_calloc(ft_strlen(buffer) - i, sizeof(char));
	if (!remainder)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
		remainder[j++] = buffer[i++];
	remainder[j] = '\0';
	free(buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_SIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_SIZE)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = ft_calloc(1, sizeof(char));
		if (!buffer[fd])
			return (NULL);
	}
	buffer[fd] = ft_find_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_extract_line(buffer[fd]);
	buffer[fd] = ft_read_line(buffer[fd]);
	if (!line)
		return (free(buffer[fd]), NULL);
	return (line);
}
/*
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			if (fd < 0)
			{
				i++;
				printf("Error");
				continue ;
			}
			while ((line = get_next_line(fd)) != NULL)
			{
				printf("%s", line);
				free(line);
			}
			close(fd);
			i++;
		}
	}
	return (0);
}
*/