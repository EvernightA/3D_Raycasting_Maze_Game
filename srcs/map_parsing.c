/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:17:34 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/08 13:36:29 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	**get_map(char *gnl, int fd, int map_height)
{
	char **map;
	int i;

	i = 0;
	map = (char **)ft_calloc(map_height + 1, sizeof(char *));
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
		if (tmp[0] != '1' && tmp[0] != '0' && tmp[0] != '\n')
		{
			//printf("tmp = %c\n", tmp[0]);
			free(tmp);
			printf("Error\nError in map\n");
			while (gnl)
			{
				free(gnl);
				gnl = get_next_line(fd);
			}
			exit (1);
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
	int count;
	char *gnl;
	char *tmp;

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

void	get_elements(int fd, t_display *display, int map_height)
{
	char	*str;
	char	*tmp;

	str = "";
	while (str)
	{
		str = get_next_line(fd);
		tmp = ft_strtrim(str, " \t");
		if (str && (tmp[0] == '1' || tmp[0] == '0'))
		{
			free(tmp);
			display->map = get_map(str, fd, map_height);
			break;
		}
		if (str)
		{
			store_texture(str, display);
		}
		else
			break;
		free(str);
		free(tmp);
	}
}
