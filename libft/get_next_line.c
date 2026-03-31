/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:11:25 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/08/19 10:12:14 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i])
	{
		i++;
	}
	if (str[i] == '\n')
		i++;
	return (i);
}

static char	*ft_insert_to_newline(char *str)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen_line(str);
	new = (char *)ft_calloc_gnl(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		if (str[i] == '\n')
			break ;
		i++;
	}
	if (str[i] == '\n')
		new[i] = '\n';
	return (new);
}

static char	*ft_update_and_free(char **line, char *stock)
{
	char	*tmp;

	tmp = ft_strdup_gnl(stock);
	*line = ft_insert_to_newline(tmp);
	free(stock);
	stock = ft_strdup_gnl(tmp + ft_strlen_line(tmp));
	free(tmp);
	return (stock);
}

static int	ft_read_text(int truth, int fd, char *buffer, char **stock)
{
	while (truth)
	{
		truth = read(fd, buffer, BUFFER_SIZE);
		if (truth < 0 || BUFFER_SIZE <= 0 || fd < 0)
		{
			free(buffer);
			free(*stock);
			*stock = NULL;
			return (1);
		}
		buffer[truth] = 0;
		if (ft_is_newline(buffer))
		{
			*stock = ft_strjoin_gnl(*stock, buffer);
			break ;
		}
		*stock = ft_strjoin_gnl(*stock, buffer);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stock = NULL;
	char		*line;
	int			truth;
	int			stop;

	buffer = (char *)ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	truth = 1;
	stop = ft_read_text(truth, fd, buffer, &stock);
	if (stop)
		return (NULL);
	free(buffer);
	stock = ft_update_and_free(&line, stock);
	if (line[0] == '\0')
	{
		free(line);
		free(stock);
		stock = NULL;
		return (NULL);
	}
	return (line);
}
