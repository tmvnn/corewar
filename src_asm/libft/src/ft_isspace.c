/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idunaver <idunaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 21:11:53 by idunaver          #+#    #+#             */
/*   Updated: 2020/01/26 14:37:43 by idunaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
	c == '\v')
		return (1);
	return (0);
}
