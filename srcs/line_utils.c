/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:55:53 by mratsima          #+#    #+#             */
/*   Updated: 2025/11/24 18:54:06 by fsamy-an         ###   ########.fr       */
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

int	ft_linesize(t_line *line)
{
	int	i;

	i = 0;
	while (line != NULL)
	{
		i++;
		line = line->next;
	}
	return (i);
}

void	print_list(t_line *head)
{
	t_line	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("x = %d\n", tmp->dot.x);
		printf("y = %d\n", tmp->dot.y);
		// printf("-----------------------\n");
		tmp = tmp->next;
	}
}
