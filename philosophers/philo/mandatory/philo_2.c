/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:12:30 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/09 21:05:17 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	meal_count(t_philo	*arr, int y)
{
	if (arr[0].ac == 6 && y == arr[0].nbr_phil)
	{
		pthread_mutex_lock(&arr[0].philo->print);
		sleeping(2);
		printf("Philosophical hunger has been sated %d times\n",
			arr[0].must_eat);
		return (1);
	}
	return (0);
}

int	number_fed(t_philo	*p)
{
	if (p->ac == 6)
	{
		p->has_eatn++;
		if (p->must_eat == p->has_eatn && p->philo->y < p->nbr_phil)
			p->philo->y++;
	}
	return (0);
}

int	get_time(struct timeval *now, t_philo	*p, int x)
{
	if (x)
		gettimeofday(now, 0);
	return (((now->tv_sec - p->philo->start.tv_sec) * 1000)
		+ ((now->tv_usec - p->philo->start.tv_usec) / 1000));
}

void	sleeping(long millisec)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while (((now.tv_sec - start.tv_sec) * 1000)
		+ (now.tv_usec - start.tv_usec) / 1000 < millisec)
	{
		usleep(250);
		gettimeofday(&now, 0);
	}
}
