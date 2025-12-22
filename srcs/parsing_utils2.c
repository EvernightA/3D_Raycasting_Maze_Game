/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 08:07:44 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/22 08:08:28 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	rgb_storing(char **rgb, char *tmp, t_display *display)
{
	if (*rgb)
		free(*rgb);
	*rgb = ft_strdup(tmp);
	display->element_count++;
}
