/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsamy-an <fsamy-an@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:14:31 by fsamy-an          #+#    #+#             */
/*   Updated: 2025/03/19 11:14:14 by fsamy-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_len(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count + 1);
}

static	char	*ft_n_max(void)
{
	char	*str;

	str = ft_strdup("-2147483648");
	return (str);
}

static void	ft_affectation(int *r, int *q, int *n)
{
	*q = *n / 10;
	*r = *n % 10;
	*n = *q;
}

static void	ft_check_negative(char *str, int *n)
{
	if (*n < 0)
	{
		str[0] = '-';
		*n = *n * -1;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		r;
	int		q;
	int		last;

	if (n == -2147483648)
	{
		str = ft_n_max();
		return (str);
	}
	last = ft_count_len(n);
	str = (char *)ft_calloc(last, sizeof(char));
	if (str == NULL)
		return (NULL);
	last--;
	ft_check_negative(str, &n);
	while (last != 0)
	{
		if (str[last - 1] == '-')
			break ;
		ft_affectation(&r, &q, &n);
		str[last - 1] = r + '0';
		last--;
	}
	return (str);
}
