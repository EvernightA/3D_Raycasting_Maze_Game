/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:13:12 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/29 08:23:18 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static void	print_number(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i != -1)
	{
		ft_putchar(str[i--]);
	}
}

static int	ft_putnbr_mem_hex(unsigned long n, char type)
{
	unsigned long	r;
	char			a[17];
	int				i;

	i = 0;
	if (n == 0)
	{
		ft_putnbr(0);
		return (1);
	}
	while (n)
	{
		if (n % 16 <= 9)
			r = n % 16 + '0';
		else
			r = n % 16 + type - 10;
		n = n / 16;
		a[i] = r;
		i++;
	}
	a[i] = '\0';
	print_number(a);
	return (i);
}

int	ft_print_memory(va_list list)
{
	int				len;
	unsigned long	number;

	len = 0;
	number = va_arg(list, unsigned long);
	if (number == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	len = len + ft_putnbr_mem_hex(number, 'a') + 2;
	return (len);
}
