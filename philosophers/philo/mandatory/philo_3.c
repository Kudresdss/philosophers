/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:17:43 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/09 21:06:20 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	is_dead(t_philo	*arr, struct timeval *now, int i)
{
	pthread_mutex_lock(&arr[0].philo->print);
	sleeping(2);
	printf("%d %d died\n", get_time(now, &arr[0], 1),
		arr[i].x_phil);
	arr[0].philo->to_end = 1;
}

void	fork_unlock(t_philo	*p)
{
	if (p->x_phil != p->nbr_phil)
	{
		pthread_mutex_unlock(&p->mutex[p->left]);
		pthread_mutex_unlock(&p->mutex[p->right]);
	}
	if (p->x_phil == p->nbr_phil)
	{
		pthread_mutex_unlock(&p->mutex[p->right]);
		pthread_mutex_unlock(&p->mutex[p->left]);
	}
}
