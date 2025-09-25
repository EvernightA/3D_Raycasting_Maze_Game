/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratsima <mratsima@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 07:23:41 by mratsima          #+#    #+#             */
/*   Updated: 2025/09/25 14:45:09 by mratsima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	ft_change_sign(long long *number, int count, int sign)
{
	if (count % 2 != 0)
	{
		*number = -*number;
	}
	if (sign > 1)
		*number = 0;
}

long long	atoll(const char *ptr)
{
	int			i;
	int			count;
	long long	atoll_number;
	int			sign;

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
	atoll_number = 0;
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		atoll_number = atoll_number * 10 + ptr[i] - '0';
		i++;
	}
	ft_change_sign(&atoll_number, count, sign);
	return (atoll_number);
}
