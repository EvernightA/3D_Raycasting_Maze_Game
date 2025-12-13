/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:37:27 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/13 14:41:57 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	sample_texture(t_img_texture *img_tex, int tex_x, int tex_y)
{
	char	*addr;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= img_tex->width)
		tex_x = img_tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= img_tex->height)
		tex_y = img_tex->height - 1;
	addr = img_tex->data + (tex_y * img_tex->line_len
			+ tex_x * (img_tex->bpp / 8));
	return (*(unsigned int *)addr);
}
