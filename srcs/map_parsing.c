/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:17:34 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/22 09:48:46 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	**get_map(char *gnl, int fd, int map_height)
{
	char	**map;
	int		i;

	i = 0;
	map = (char **)ft_calloc(map_height + 1, sizeof(char *));
	if (!map)
		return (NULL);
	while (i < map_height)
	{
		map[i++] = ft_strdup(gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	while (gnl)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
	return (map);
}

void	count_lines(char *gnl, char *tmp, int *count, int fd)
{
	while (gnl)
	{
		if (tmp[0] != '1' && tmp[0] != '0')
		{
			free(tmp);
			printf("Error\nError in map\n");
			while (gnl)
			{
				free(gnl);
				gnl = get_next_line(fd);
			}
			exit(1);
		}
		(*count)++;
		free(gnl);
		free(tmp);
		gnl = get_next_line(fd);
		tmp = ft_strtrim(gnl, " \t");
	}
	while (gnl)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
}

int	count_map_lines(int fd)
{
	int		count;
	char	*gnl;
	char	*tmp;

	count = 0;
	gnl = get_next_line(fd);
	tmp = ft_strtrim(gnl, " \t");
	while (gnl)
	{
		if (tmp && (tmp[0] == '0' || tmp[0] == '1'))
			break ;
		free(gnl);
		free(tmp);
		gnl = get_next_line(fd);
		tmp = ft_strtrim(gnl, " \t");
	}
	count_lines(gnl, tmp, &count, fd);
	return (count);
}

void	exhaust_gnl(char *str, int fd)
{
	while (str)
	{
		free(str);
		str = get_next_line(fd);
	}
}

int	get_elements(int fd, t_display *display, int map_height)
{
	char	*str;
	char	*tmp;
	char	*tmp2;

	str = "";
	tmp2 = NULL;
	while (str)
	{
		str = get_next_line(fd);
		tmp = ft_strtrim(str, " \t");
		if (str && (tmp[0] == '1' || tmp[0] == '0'))
		{
			free(tmp);
			display->map = get_map(str, fd, map_height);
			break ;
		}
		if (str && store_texture(tmp2, str, display))
		{
			exhaust_gnl(str, fd);
			return (free(tmp), 1);
		}
		free(str);
		free(tmp);
	}
	return (0);
}
