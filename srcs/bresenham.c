/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:17:03 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/10/28 15:13:38 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

t_line	*bresenham_line(t_point *begin, t_point *end)
{
	int delta_x;
	int delta_y;
	int x_step;
	int y_step;
	int err;
	int dp;
	t_point current;
	t_line *head;
	t_line *new_node;
	
	head = NULL;
	delta_x = ft_abs(end->x - begin->x);
	delta_y = ft_abs(end->y - begin->y);
	if ((begin->x < end->x))
		x_step = 1;
	else
		x_step = -1;
	if ((begin->y < end->y))
		y_step = 1;
	else
		y_step = -1;
	err = delta_x - delta_y;
	current = *begin;
	while (1)
	{
		new_node = ft_linenew(current);
		ft_lineadd_back(&head, new_node);
		if (head == NULL)
			head = new_node;
		if (current.x == end->x && current.y == end->y)
			break ;
		dp = 2 * err;
		if (dp > -delta_y)
		{
			err -= delta_y;
			current.x += x_step;
		}
		if (dp < delta_x)
		{
			err += delta_x;
			current.y += y_step;
		}
	}
	return (head);
}

//t_line	*bresenham_line(t_point *begin, t_point *end)
//{
//	int delta_x;
//	int delta_y;
//	//int i;
//	int x_step;
//	int y_step;
//	t_point next_point;
//	t_line *head;
//	t_line *new_node;
//	//
//	//i = 0;
//	head = NULL;
//	delta_x = abs(end->x - begin->x);
//	delta_y = abs(end->y - begin->y);
//	if (begin->x < end->x)
//		x_step = 1;
//	else	
//		x_step = -1;
//	if (begin->y < end->y)
//		y_step = 1;
//	else
//		y_step = -1;
//	//if (abs(delta_y) < abs(delta_x))
//	//	begin->dp = 2 * (delta_y - delta_x);
//	//else
//	//	begin->dp = 2 * (delta_x - delta_y);
//	next_point.x = begin->x;
//	next_point.y = begin->y;
//	begin->dp = delta_x - delta_y;
//	while (1)
//	{
//		if ((begin->x == end->x && begin->y == end->y)/* || i > delta_x - 1*/)
//		{
//			new_node = ft_linenew(*begin);
//			ft_lineadd_back(&head,new_node);
//			break ;
//		}
//		new_node = ft_linenew(*begin);
//		ft_lineadd_back(&head,new_node);
//		//if (i == 0)
//		//{
//			//head = new_node;
//		//}
//		if (begin->dp < 0)
//		{
//			if (abs(delta_y) < abs(delta_x))
//			{
//				next_point.dp = begin->dp + 2 * delta_y;
//				next_point.x = begin->x + x_step;
//			}
//			else
//			{
//				next_point.dp = begin->dp + 2 * delta_x;
//				next_point.y = begin->y + y_step;
//			}
//		}
//		else
//		{
//			if (abs(delta_y) < abs(delta_x))
//			{
//				next_point.dp = begin->dp + 2 * (delta_y - delta_x);
//				next_point.x = begin->x + x_step;
//			}
//			else
//			{
//				next_point.dp = begin->dp + 2 * (delta_x - delta_y);
//				next_point.y = begin->y + y_step;
//			}
//		}
//		//next_point.x = begin->x + x_step;
//		//next_point.y = begin->y + y_step;
//		begin = &next_point;
//		//i++;
//	}
//	return (head);
//}

//t_line	*bresenham_line(t_point *begin, t_point *end)
//{
//	int delta_x;
//	int delta_y;
//	int i;
//	int x_step;
//	int y_step;
//	t_point next_point;
//	t_line *head;
//	t_line *new_node;
//	int error;
//	//
//	i = 0;
//	head = NULL;
//	delta_x = abs(end->x - begin->x);
//	delta_y = abs(end->y - begin->y);
//	if (begin->x < end->x)
//		x_step = 1;
//	else	
//		x_step = -1;
//	if (begin->y < end->y)
//		y_step = 1;
//	else
//		y_step = -1;
//	//
//	if (abs(delta_y) < abs(delta_x))
//		error =  (delta_y - delta_x);
//	else
//		error =  (delta_x - delta_y);
//	next_point.x = begin->x ;
//	next_point.y = begin->y ;
//	head = NULL;
//	begin->dp = 2 * error;
//	while (1)
//	{
//		if ((begin->x > end->x && begin->y > end->y) || i > delta_x - 1)
//		{
//			new_node = ft_linenew(*begin);
//			ft_lineadd_back(&head,new_node);
//			break ;
//		}
//		new_node = ft_linenew(*begin);
//		ft_lineadd_back(&head,new_node);
//		if (i == 0)
//		{
//			head = new_node;
//		}
//		if (begin->dp > -delta_y)
//		{
//			error -= delta_y;
//			next_point.x += x_step;
//			begin->dp = 2 * error;
//		}
//		if (begin->dp < delta_x)
//		{
//			error += delta_x;
//			next_point.y += y_step;
//			begin->dp = 2 * error;
//		}
//		begin = &next_point;
//		i++;
//	}
//	return (head);
//}