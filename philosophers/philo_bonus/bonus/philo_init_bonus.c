/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 07:01:01 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/08 07:29:44 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo_bonus.h"

int	init_pid(t_philo	*phil)
{
	pid_t	*pid;

	pid = (pid_t *)malloc(sizeof(pid_t) * phil->nbr_phil);
	if (pid == NULL)
	{
		write(2, "Error\nmalloc() failed\n", 22);
		return (1);
	}
	phil->pid = pid;
	return (0);
}

int	init_2(t_philo	*phil)
{
	sem_unlink("forks");
	sem_unlink("print");
	phil->sem = sem_open("forks", O_CREAT, S_IRWXU, phil->nbr_phil);
	phil->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	if (phil->sem == SEM_FAILED || phil->print == SEM_FAILED)
	{
		write(2, "Error:\nsem_open() failed\n", 25);
		return (5);
	}
	return (0);
}

int	init_philo(t_philo	*phil, int ac, char	**av)
{
	int	ret;

	phil->ac = ac;
	phil->dead = 0;
	phil->to_end = 0;
	phil->x_to_end = 0;
	phil->nbr_phil = ft_atoi(av[1]);
	phil->t_to_die = 1000 * ft_atoi(av[2]);
	phil->t_to_eat = 1000 * ft_atoi(av[3]);
	phil->t_to_slp = 1000 * ft_atoi(av[4]);
	if (phil->nbr_phil <= 0 || phil->t_to_die <= 0
		|| phil->t_to_eat < 0 || phil->t_to_slp < 0)
		return (2);
	else if (phil->ac == 6)
	{
		phil->must_eat = ft_atoi(av[5]);
		phil->has_eatn = 0;
		if (phil->must_eat <= 0)
			return (2);
	}
	else if (phil->nbr_phil > 250)
		return (3);
	init_2(phil);
	ret = start_philo(phil);
	return (ret);
}
