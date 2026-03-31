/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:54:09 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/14 17:48:34 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_change_sign(int *number, int count, int sign)
{
	if (count % 2 != 0)
	{
		*number = -*number;
	}
	if (sign > 1)
		*number = 0;
}

int	ft_atoi(const char *ptr)
{
	int	i;
	int	count;
	int	atoi_number;
	int	sign;

	i = 0;
	count = 0;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == 32)
		i++;
	sign = 0;
	while (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			count++;
		i++;
		sign++;
	}
	atoi_number = 0;
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		atoi_number = atoi_number * 10 + ptr[i] - '0';
		i++;
	}
	ft_change_sign(&atoi_number, count, sign);
	return (atoi_number);
}
