/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:12:30 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/08 17:30:56 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	meal_count(t_philo	*arr, int i, int y)
{
	if (arr[0].ac == 6 && arr[i].has_eatn == arr[0].must_eat)
	{
		if (y == arr[0].nbr_phil)
		{
			printf("Philosophical hunger has been sated %d times\n",
				arr[0].must_eat);
			return (1);
		}
	}
	return (0);
}

int	return_or_not(t_philo	*p)
{
	if (p->ac == 6)
	{
		p->has_eatn++;
		if (p->must_eat == p->has_eatn)
		{
			p->philo->y++;
			return (1);
		}
	}
	if (p->nbr_phil == 1)
		return (1);
	return (0);
}

int	get_time(struct timeval *now, t_philo	*p, int x)
{
	if (x)
		gettimeofday(now, 0);
	return (((now->tv_sec - p->philo->start.tv_sec) * 1000)
		+ ((now->tv_usec - p->philo->start.tv_usec) / 1000));
}

void	sleeping(long microsec)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while (((now.tv_sec - start.tv_sec) * 1000000)
		+ (now.tv_usec - start.tv_usec) < microsec)
	{
		usleep(10);
		gettimeofday(&now, 0);
	}
}

int	free_all(t_philo	**arr, int x, int y)
{
	int	i;

	i = 0;
	while (i < arr[0]->nbr_phil)
	{
		pthread_mutex_destroy(&arr[0]->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&arr[0]->is_ded);
	pthread_mutex_destroy(&arr[0]->print);
	free(arr[0]->mutex);
	free(arr[0]->id);
	i = 0;
	if (x)
		y = arr[0]->nbr_phil;
	while (i < y)
		free(arr[i++]);
	free(arr);
	if (!x)
		return (2);
	return (0);
}
