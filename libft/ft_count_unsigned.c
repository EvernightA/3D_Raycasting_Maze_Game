/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:44:55 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/27 16:33:08 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_count_unsigned(va_list list)
{
	size_t			count;
	unsigned int	number;

	number = va_arg(list, unsigned int);
	count = 0;
	ft_putnbr_unsigned(number);
	if (number == 0)
		return (1);
	while (number)
	{
		number = number / 10;
		count++;
	}
	return (count);
}
