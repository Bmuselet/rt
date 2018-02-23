/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 11:45:16 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/23 11:46:01 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(int c)
{
	if ((c >= '0' && c <= '9') || c == '+' || c == '-')
		return (1);
	return (0);
}