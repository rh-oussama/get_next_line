/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:25:44 by orhaddao          #+#    #+#             */
/*   Updated: 2023/11/21 19:00:51 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_file(int fd, char *tmp)
{
	char	*buffer;
	int		bytes_read;
	char	*t;

	bytes_read = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(tmp);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		t = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = t;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (tmp);
}

char	*get_line_file(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = calloc(i + 2, 1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*get_next(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	new_buffer = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_calloc((ft_strlen(buffer) - i + 1), 1);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free (buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*extracted_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = get_file(fd, buff);
	if (!buff)
		return (NULL);
	extracted_line = get_line_file(buff);
	buff = get_next(buff);
	return (extracted_line);
}

// int main(void)
// {
// 	int fd = open("file.txt", O_RDONLY);
// 	char *line;

// 	line = get_next_line(fd);
// 	printf("line: |%s|\n", line);
// 	line = get_next_line(fd);
// 	printf("line: |%s|\n", line);
// 	line = get_next_line(fd);
// 	printf("line: |%s|\n", line);
// 	free(line);
// 	close(fd);
// 	return 0;
// }