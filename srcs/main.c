/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:22:35 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/20 14:30:02 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	display_map(int fd, t_tex *texture)
{
	char	*str;
	char	*tmp;

	str = "";
	while (str)
	{
		str = get_next_line(fd);
		if (str)
		{
			tmp = ft_strtrim(str, " \t");
			if (ft_strncmp("NO", tmp, 2) == 0)
			{
				texture->north = ft_strdup("NO");
				printf("north ok\n");
			}
			else if (ft_strncmp("SO", tmp, 2) == 0)
			{
				texture->south = ft_strdup("SO");
				printf("south ok\n");
			}
			else if (ft_strncmp("WE", tmp, 2) == 0)
			{
				texture->west = ft_strdup("WE");
				printf("west ok\n");
			}
			else if (ft_strncmp("EA", tmp, 2) == 0)
			{
				texture->east = ft_strdup("EA");
				printf("east ok\n");
			}
		}
		else
			break;
		ft_putstr_fd(tmp ,1);
		free(str);
		free(tmp);
	}
}

void	init_it(t_tex *text)
{
	text->north = NULL;
	text->south = NULL;
	text->east = NULL;
	text->west =  NULL;
}
int	main(int argc, char **argv)
{
	(void)argv;
	int fd;
	t_tex	texture;
	
	init_it(&texture);
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <path to the map>\n",2);
		return (0);
	}
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nNo such file or directory\n",2);
		return (0);
	}
	display_map(fd, &texture);



	return (0);
}