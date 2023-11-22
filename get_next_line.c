/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:25:44 by orhaddao          #+#    #+#             */
/*   Updated: 2023/11/22 20:28:38 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_file(int fd, char *tmp)
{
	char	*buffer;
	int		bytes_read;
	char	*new_tmp;

	bytes_read = 1;
	buffer = (char *) ft_calloc(BUFFER_SIZE + 1, 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(tmp), NULL);
		buffer[bytes_read] = '\0';
		new_tmp = ft_strjoin(tmp, buffer);
		if (!new_tmp)
			return (free(buffer), NULL);
		free(tmp);
		tmp = new_tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (tmp);
}

char	*get_line_file(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (ft_strlen(buffer) == 0)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		if (buffer[i] == '\n')
			break ;
		i++;
	}
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

int main(void)
{
	int fd = open("file.txt", O_RDONLY);
	char *line;

	line = get_next_line(fd);
	printf("line: |%s|\n", line);
	line = get_next_line(fd);
	printf("line: |%s|\n", line);
	line = get_next_line(fd);
	printf("line: |%s|\n", line);
	free(line);
	close(fd);
	return 0;
}