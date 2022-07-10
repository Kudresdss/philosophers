/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:58:17 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/10 17:19:51 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo_bonus.h"

void	to_close_sem(t_philo	*phil)
{
	sem_close(phil->sem);
	sem_close(phil->print);
	sem_close(phil->is_dead);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("is_dead");
}

void	clean_all(t_philo	*phil)
{
	int	i;

	i = 0;
	while (i < phil->nbr_phil)
	{
		kill(phil->pid[i], 9);
		i++;
	}
	to_close_sem(phil);
	free(phil->pid);
}
