/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:01:05 by ymirna            #+#    #+#             */
/*   Updated: 2022/06/11 14:35:40 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_atoi(const char	*str)
{
	size_t				i;
	int					ng;
	unsigned long long	s;

	i = 0;
	s = 0;
	ng = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ng = -ng;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		s = s * 10 + (str[i++] - '0');
		if (ng > 0 && s >= 9223372036854775807)
			return (-1);
		if (ng < 0 && s > 9223372036854775807)
			return (0);
	}
	return (s * ng);
}
