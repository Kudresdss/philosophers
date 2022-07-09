/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 03:28:01 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/09 22:17:32 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	munch(t_philo	*p, struct timeval *now)
{
	// if (p->x_phil != p->nbr_phil)
	// 	pthread_mutex_lock(&p->mutex[p->right]);
	// else
		pthread_mutex_lock(&p->mutex[p->left]);
	pthread_mutex_lock(&p->philo->print);
	printf("%d %d has taken a fork\n", get_time(now, p, 1), p->x_phil);
	pthread_mutex_unlock(&p->philo->print);
	if (p->nbr_phil == 1)
		return (1);
	// if (p->x_phil != p->nbr_phil)
	// 	pthread_mutex_lock(&p->mutex[p->left]);
	// else
		pthread_mutex_lock(&p->mutex[p->right]);
	pthread_mutex_lock(&p->philo->is_ded);
	gettimeofday(&p->last_fed, 0);
	pthread_mutex_unlock(&p->philo->is_ded);
	pthread_mutex_lock(&p->philo->print);
	printf("%d %d has taken a fork\n", get_time(now, p, 1), p->x_phil);
	printf("%d %d is eating\n", get_time(now, p, 1), p->x_phil);
	pthread_mutex_unlock(&p->philo->print);
	sleeping(p->t_to_eat);
	number_fed(p);
	return (0);
}

void	time_to_sleep(t_philo	*p, struct timeval *now)
{
	pthread_mutex_lock(&p->philo->print);
	printf("%d %d is sleeping\n", get_time(now, p, 1), p->x_phil);
	pthread_mutex_unlock(&p->philo->print);
	sleeping(p->t_to_slp);
	pthread_mutex_lock(&p->philo->print);
	printf("%d %d is thinking\n", get_time(now, p, 1), p->x_phil);
	pthread_mutex_unlock(&p->philo->print);
}

void	*philo(void	*phil)
{
	t_philo			*p;
	struct timeval	now;

	p = (t_philo *)phil;
	p->last_fed.tv_sec = p->philo->start.tv_sec;
	p->last_fed.tv_usec = p->philo->start.tv_usec;
	if (p->x_phil % 2 == 0)
		sleeping(2);
	while (1)
	{
		if (munch(p, &now))
		{
			fork_unlock(p);
			return (0);
		}
		fork_unlock(p);
		time_to_sleep(p, &now);
	}
	return (0);
}

void	watch_philo(t_philo	*arr)
{
	int				i;
	struct timeval	now;

	while (1)
	{
		i = 0;
		while (i < arr[0].nbr_phil)
		{
			if (meal_count(arr, arr[0].philo->y))
				return ;
			pthread_mutex_lock(&arr[0].philo->is_ded);
			if (arr[0].t_to_die < get_time(&now, &arr[0], 1)
				- get_time(&arr[i].last_fed, &arr[0], 0))
			{
				is_dead(arr, &now, i);
				return ;
			}
			pthread_mutex_unlock(&arr[0].philo->is_ded);
			i++;
		}
	}
}

void	start_philo(t_philo	*arr)
{
	int			i;

	i = 0;
	arr[0].philo->y = 0;
	gettimeofday(&arr[0].philo->start, 0);
	while (i < arr[0].nbr_phil)
	{
		pthread_create(&arr[0].id[i], 0, philo, &arr[i]);
		pthread_detach((arr[0]).id[i]);
		i++;
	}
	watch_philo(arr);
		i = 0;
	while (i < arr[0].nbr_phil)
	{
		pthread_mutex_destroy(&arr[0].mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&arr[0].is_ded);
	pthread_mutex_destroy(&arr[0].print);
}
