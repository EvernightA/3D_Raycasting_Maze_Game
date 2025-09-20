/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 10:22:35 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/20 11:38:42 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
/*
read in the file

use gnl
*/

void	display_map(int fd)
{
	char	*str;

	//str = NULL;
	while (str)
	{
		str = get_next_line(fd);
		ft_putstr_fd(str ,1);
		free(str);
	}
}
int	main(int argc, char **argv)
{
	(void)argv;
	int fd;
	
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
	display_map(fd);



	return (0);
}