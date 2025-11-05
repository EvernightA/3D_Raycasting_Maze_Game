/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:17:26 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/11/05 09:23:59 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


int		shifter(int	number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (pow(2, i) == number)
		{
			return (i);
		}
		i++;
	}
	printf("Not valid nuber for size\n");
	return(0);
}
