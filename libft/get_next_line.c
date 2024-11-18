/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:12:40 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/18 10:39:51 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"
#include "./libft.h"

char *get_next_line(int fd, char *limiter)
{
    static char *line;      // Holds leftover text
    char        *buffer;    // Temporary buffer for reading

    if (fd < 0 || BUFFER_SIZE <= 0 || !limiter)
        return (NULL);
    buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!buffer)
        return (NULL);
    // Read and fill the input buffer
    line = filled_line(fd, buffer, line, limiter);
    if (!line) 
	{
        free(buffer);
        return (NULL);
    }
    // Update `line` to store leftover content before limiter
    line = left_char(line, limiter);
    if (!line || !line[0])
    {
        free(line);
        line = NULL;
    }
    return (line);
}

char *filled_line(int fd, char *buffer, char *line, char *limiter)
{
    int val_read;

    if (!line)
        line = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!line)
        return (free(buffer), NULL);

    val_read = 1;
    while (val_read && !gnl_substrchr(line, limiter))
    {
        val_read = read(fd, buffer, BUFFER_SIZE);
        if (val_read == -1)
            return (free(buffer), free(line), NULL);
        if (val_read == 0)
            break;
        buffer[val_read] = '\0';
        line = gnl_strjoin(line, buffer);
        if (!line)
            return (free(buffer), NULL);
    }

    free(buffer);
    return (line);
}

char *left_char(char *line, char *limiter)
{
    char *end_of_line;
    char *remaining_line;
    int len_before_limiter;
	int i = 0;
    // Find the position of the limiter in the line
    end_of_line = gnl_substrchr(line, limiter);
    if (!end_of_line)
        return (free(line), NULL); // No limiter found, return NULL
    // Calculate length before the limiter
    len_before_limiter = end_of_line - line;
    // Allocate memory for the string before the limiter (excluding the limiter itself)
    remaining_line = gnl_calloc(len_before_limiter + 1, sizeof(char));
    if (!remaining_line)
        return (free(line), NULL);
    // Copy everything before the limiter into remaining_line
    while ( i < len_before_limiter)
	{
        remaining_line[i] = line[i];
		i++;
	}
	remaining_line[i] = '\0';
    // Free the original line as it is no longer needed
    free(line);
    return (remaining_line);
}


/*
int main(void)
{
	int	fd;
//	char	*str;
	int	i;

	i = 0;
	fd = open("test", O_RDONLY);
	while (i < 6)
	{
		printf("%s",get_next_line(fd));
		free(get_next_line(fd));
		i++;
	}
	while ((str = get_next_line(fd))) {
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);

}
*/
