/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_condition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:49:26 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/27 15:25:46 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_condition_all(const char *string, int *len, int *i, va_list list)
{
	int	n;
	int	c;

	if (string[*i] == 'x')
		*len = *len + ft_putnbr_hex(list, 'a') - 2;
	else if (string[*i] == 'X')
		*len = *len + ft_putnbr_hex(list, 'A') - 2;
	else if (string[*i] == 'u')
		*len = *len + ft_count_unsigned(list) - 2;
	else if (string[*i] == 'd' || string[*i] == 'i')
	{
		n = va_arg(list, int);
		ft_putnbr(n);
		*len = *len + ft_count_number(n) - 2;
	}
	else if (string[*i] == 'c')
	{
		c = va_arg(list, int);
		ft_putchar(c);
		*len = *len + 1 - 2;
	}
	else if (string[*i] == 'p')
		*len = *len + ft_print_memory(list) - 2;
	else if (string[*i] == 's')
		*len = *len + ft_putstr_and_len(list, 1) - 2;
}
