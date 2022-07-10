/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:55:29 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/10 15:39:19 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo_bonus.h"

int	get_time(struct timeval *now, t_philo	*p, int x)
{
	if (x)
		gettimeofday(now, 0);
	return (((now->tv_sec - p->start.tv_sec) * 1000)
		+ ((now->tv_usec - p->start.tv_usec) / 1000));
}

void	sleeping(long microsec)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while (((now.tv_sec - start.tv_sec) * 1000)
		+ (now.tv_usec - start.tv_usec) / 1000 < microsec / 1000)
	{
		usleep(250);
		gettimeofday(&now, 0);
	}
}
