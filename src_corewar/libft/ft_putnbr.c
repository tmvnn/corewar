/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:05:54 by astanton          #+#    #+#             */
/*   Updated: 2018/12/13 14:23:30 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int nbr;
	int i;

	nbr = n;
	i = 1;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	while (nbr /= 10)
		i *= 10;
	while (i >= 1)
	{
		nbr = n / i;
		ft_putchar(nbr + '0');
		n %= i;
		i /= 10;
	}
}
