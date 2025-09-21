/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:58:59 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/09/20 22:05:38 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_tex
{
	int		completed;
	char 	*north;
	char 	*south;
	char 	*east;
	char 	*west;
	char	*c_rgb;
	char	*f_rgb;
	char	**map;

} t_tex;

#endif