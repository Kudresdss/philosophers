/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:27:55 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/10 16:06:26 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	assign_philo(t_philo	*arr, t_philo	*phil, int i)
{
	arr[i].ac = phil->ac;
	arr[i].nbr_phil = phil->nbr_phil;
	arr[i].t_to_die = phil->t_to_die;
	arr[i].t_to_eat = phil->t_to_eat;
	arr[i].t_to_slp = phil->t_to_slp;
	if (phil->ac == 6)
	{
		arr[i].must_eat = phil->must_eat;
		arr[i].has_eatn = 0;
	}
	arr[i].id = phil->id;
	arr[i].mutex = phil->mutex;
	arr[i].print = phil->print;
	arr[i].is_ded = phil->is_ded;
	arr[i].philo = phil;
	arr[i].x_phil = i + 1;
	arr[i].left = i;
	arr[i].right = i + 1;
	if (i == phil->nbr_phil - 1)
		arr[i].right = 0;
}

int	init_philo_2(t_philo	*arr, t_philo	*phil)
{
	int						i;
	pthread_t				id[250];
	pthread_mutex_t			mutex[250];

	i = 0;
	while (i < phil->nbr_phil)
	{
		pthread_mutex_init(&mutex[i], 0);
		i++;
	}	
	pthread_mutex_init(&phil->print, 0);
	pthread_mutex_init(&phil->is_ded, 0);
	phil->id = id;
	phil->mutex = mutex;
	i = 0;
	while (i < phil->nbr_phil)
	{
		assign_philo(arr, phil, i);
		i++;
	}
	return (0);
}

int	init_philo(t_philo	*arr, int ac, char	**av)
{
	t_philo	phil;

	phil.ac = ac;
	phil.x_phil = 0;
	phil.to_end = 0;
	phil.nbr_phil = ft_atoi(av[1]);
	phil.t_to_die = ft_atoi(av[2]);
	phil.t_to_eat = ft_atoi(av[3]);
	phil.t_to_slp = ft_atoi(av[4]);
	if (phil.nbr_phil <= 0 || phil.t_to_die <= 0
		|| phil.t_to_eat <= 0 || phil.t_to_slp <= 0)
		return (2);
	else if (phil.ac == 6)
	{
		phil.must_eat = ft_atoi(av[5]);
		if (phil.must_eat <= 0)
			return (2);
	}
	else if (phil.nbr_phil > 250)
		return (3);
	init_philo_2(arr, &phil);
	start_philo(arr);
	return (0);
}

int	main(int ac, char	**av)
{
	t_philo	arr[250];
	int		ret;

	if (ac != 5 && ac != 6)
	{
		write(2, "Error:\nInvalid number of arguments\n", 36);
		return (1);
	}
	ret = init_philo(arr, ac, av);
	if (ret == 2)
		write(2, "Invalid argument values\n", 24);
	else if (ret == 3)
		write(2, "Too many philosophers\n", 22);
	return (ret);
}
