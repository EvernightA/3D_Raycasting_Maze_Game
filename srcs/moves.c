/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:41:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/13 18:54:32 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int releasing_key(int key, void *param)
{
    t_display  *display;

    display = (t_display *)param;
    (void)display;
    if (key == XK_W || key == XK_w)
    {
        display->key_stat.w_press = false;
        printf("W released\n");
    }
    if (key == XK_A || key == XK_a)
    {
        display->key_stat.a_press = false;
        printf("A released\n");

    }
    if (key == XK_S || key == XK_s)
    {
        display->key_stat.s_press = false;
        printf("S released\n");

    }
    if (key == XK_D || key == XK_d)
    {
        display->key_stat.d_press = false;
        printf("D released\n");

    }
    if (key == XK_Left)
    {
        display->key_stat.left_press = false;
        printf("Left released\n");

    }
    if (key == XK_Right)
    {
        display->key_stat.right_press = false;
        printf("Right released\n");

    }
    return (0);
}

// void    game_engine(t_display *display)
// {
//     while (1)
//     {

//     }
// }