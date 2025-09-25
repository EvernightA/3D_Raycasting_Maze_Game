/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:00:37 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/25 16:17:53 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int texture_error(t_tex *texture)
{
	char *tmp;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	tmp = ft_strnstr(texture->north, ".xpm", ft_strlen(texture->north));
	tmp1 = ft_strnstr(texture->south, ".xpm", ft_strlen(texture->south));
	tmp2 = ft_strnstr(texture->west, ".xpm", ft_strlen(texture->west));
	tmp3 = ft_strnstr(texture->east, ".xpm", ft_strlen(texture->east));
	if (tmp == NULL || tmp1 ==  NULL || tmp2 == NULL || tmp3 == NULL)
	{
		ft_putstr_fd("Error\nInvalid extension for texture\n", 2);
		return (1);
	}
	if (ft_strncmp(tmp, ".xpm", 5) != 0 || ft_strncmp(tmp1, ".xpm", 5) != 0 
	|| ft_strncmp(tmp2, ".xpm", 5) != 0 || ft_strncmp(tmp3, ".xpm", 5) != 0)
 	{
		ft_putstr_fd("Error\nInvalid extension for texture\n", 2);
		return (1);
	}
	return (0);
}

