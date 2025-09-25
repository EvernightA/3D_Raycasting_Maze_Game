/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:50:26 by mratsima          #+#    #+#             */
/*   Updated: 2025/09/25 11:51:16 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	quit_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(0);
}

int key_hook(int key, void *param)
{
	if (key == K_ESC)
		quit_win((t_mlx *)param);
	return (0);
}