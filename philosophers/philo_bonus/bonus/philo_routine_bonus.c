/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 07:32:05 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/09 18:39:55 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo_bonus.h"

void	*watch_philo(void	*p)
{
	struct timeval	now;
	t_philo			*phil;

	phil = (t_philo *)p;
	while (1)
	{
		sem_close(phil->is_dead);
		if (phil->t_to_die / 1000 < get_time(&now, phil, 1)
			- get_time(&phil->last_fed, phil, 0))
		{
			sem_wait(phil->print);
			printf("%d %d died\n", get_time(&now, phil, 1),
				phil->x_phil);
			exit(1);
		}
		sem_post(phil->is_dead);
		sleeping(2000);
	}
}

void	philo_forks(t_philo	*phil, struct timeval *now)
{
	sem_wait(phil->sem);
	sem_wait(phil->print);
	printf("%d %d has taken a fork\n",
		get_time(now, phil, 1), phil->x_phil);
	sem_post(phil->print);
	sem_wait(phil->sem);
	sem_close(phil->is_dead);
	gettimeofday(&phil->last_fed, 0);
	sem_post(phil->is_dead);
	sem_wait(phil->print);
	printf("%d %d has taken a fork\n",
		get_time(now, phil, 1), phil->x_phil);
	printf("%d %d is eating\n", get_time(now, phil, 1), phil->x_phil);
	sem_post(phil->print);
	sleeping(phil->t_to_eat);
	sem_post(phil->sem);
	sem_post(phil->sem);
}

void	philo_slp_and_thnk(t_philo	*phil, struct timeval *now)
{
	sem_wait(phil->print);
	printf("%d %d is sleeping\n", get_time(now, phil, 1), phil->x_phil);
	sem_post(phil->print);
	sleeping(phil->t_to_slp);
	sem_wait(phil->print);
	printf("%d %d is thinking\n", get_time(now, phil, 1), phil->x_phil);
	sem_post(phil->print);
}

void	philo(t_philo	*phil, int i)
{
	struct timeval	now;
	pthread_t		id;

	phil->x_phil = i;
	phil->last_fed.tv_sec = phil->start.tv_sec;
	phil->last_fed.tv_usec = phil->start.tv_usec;
	pthread_create(&id, 0, watch_philo, phil);
	pthread_detach(id);
	while (1)
	{
		philo_forks(phil, &now);
		if (phil->ac == 6)
		{
			phil->has_eatn++;
			if (phil->has_eatn == phil->must_eat)
				exit(2);
		}
		philo_slp_and_thnk(phil, &now);
	}
}
