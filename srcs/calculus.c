/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:17:26 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/19 13:38:10 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


int		shifter(int	number)
{
	int	i;
	int power;
	int max_bits;

	i = 0;
	power = 1;
	max_bits = 32;
	while (i < max_bits)
	{
		if (power == number)
			return (i);
		power = power << 1;
		i++;
	}
	printf("Not valid number for size\n");
	return(0);
}
