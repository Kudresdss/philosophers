/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:12:30 by ymirna            #+#    #+#             */
/*   Updated: 2022/06/25 18:55:47 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	get_time(struct timeval	*now, t_philo	*p)
{
	gettimeofday(now, 0);
	return (((now->tv_sec - p->philo->start.tv_sec) * 1000)
			+ ((now->tv_usec - p->philo->start.tv_usec) / 1000));
}

void	sleeping(long sec)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while ((now.tv_sec - start.tv_sec) +
			(now.tv_usec - start.tv_usec) < sec)
	{
		usleep(10);
		gettimeofday(&now, 0);
	}
}

int	free_arr(t_philo	**arr, int	i)
{
	while (i)
	{
		free(arr[i]);
		i--;
	}
	return (2);
}
