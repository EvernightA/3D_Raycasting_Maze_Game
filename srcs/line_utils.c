/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:55:53 by mratsima          #+#    #+#             */
/*   Updated: 2025/12/13 15:48:51 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_linefree(t_line **line)
{
	t_line	*node;
	t_line	*prev;
	t_line	*next;

	node = *line;
	prev = node;
	if (!line)
		return ;
	while (node != NULL)
	{
		prev = node;
		next = prev->next;
		free(node);
		node = next;
	}
	*line = NULL;
}

t_line	*ft_linenew(t_point content)
{
	t_line	*new_node;

	new_node = (t_line *)malloc(sizeof(t_line));
	if (new_node == NULL)
		return (NULL);
	new_node->dot = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lineadd_back(t_line **line, t_line *new)
{
	t_line	*tmp;

	if (*line == NULL)
	{
		*line = new;
		return ;
	}
	tmp = *line;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

int	is_valid_map_pos(t_display *display)
{
	if (display->ray.map_y < 0
		|| display->ray.map_y >= display->texture.map_height)
		return (0);
	if (display->ray.map_x < 0
		|| display->ray.map_x >= display->texture.map_width)
		return (0);
	if (!display->map[display->ray.map_y][display->ray.map_x])
		return (0);
	return (1);
}
