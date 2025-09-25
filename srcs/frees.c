/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:22:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/09/25 11:27:22 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

void	free_texture(t_tex *texture)
{
	free_split(texture->map);
	free(texture->c_rgb);
	free(texture->f_rgb);
	free(texture->east);
	free(texture->north);
	free(texture->west);
	free(texture->south);
}

