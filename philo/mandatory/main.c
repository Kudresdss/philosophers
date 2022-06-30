/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:27:55 by ymirna            #+#    #+#             */
/*   Updated: 2022/06/30 16:47:25 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*philo(void	*phil)
{
	t_philo			*p;
	struct timeval	now;

	p = (t_philo *)phil;
	while (1)
	{
		pthread_mutex_lock(&p->mutex[p->left]);
		pthread_mutex_lock(&p->print);
		printf("%d %d has taken a fork\n", get_time(&now, p), p->x_phil);
		pthread_mutex_unlock(&p->print);
		pthread_mutex_lock(&p->mutex[p->right]);
		pthread_mutex_lock(&p->print);
		printf("%d %d is eating\n", get_time(&now, p), p->x_phil);
		pthread_mutex_unlock(&p->print);
		sleeping(p->t_to_eat);
		pthread_mutex_unlock(&p->mutex[p->right]);
		pthread_mutex_unlock(&p->mutex[p->left]);
		gettimeofday(&p->last_fed, 0);
		pthread_mutex_lock(&p->print);
		printf("%d %d is sleeping\n", get_time(&now, p), p->x_phil);
		pthread_mutex_unlock(&p->print);
		sleeping(p->t_to_slp);
		pthread_mutex_lock(&p->print);
		printf("%d %d is thinking\n", get_time(&now, p), p->x_phil);
		pthread_mutex_unlock(&p->print);
		if (p->ac == 6)
		{
			p->has_eatn++;
			if (p->must_eat == p->has_eatn)
				return (0);
		}
	}
	return (0);
}

void	watch_philo(t_philo	**arr)
{
	int	i;
	struct timeval	now;

	while (1)
	{
		i = 0;
		while (i < arr[0]->nbr_phil)
		{
			if (arr[0]->t_to_die <= get_time(&arr[i]->last_fed, 0))
			{
				printf("%d %d died\n", get_time(&now, arr[i]), arr[i]->x_phil);
				return;
			}
			i++;
		}
	}
	
}

void	start_philo(t_philo	**arr)
{
	void		*ret;
	int			i;

	i = 1;
	(void) ret;

	while (i < arr[0]->nbr_phil)
	{
		pthread_create(&(arr[0])->id[i], 0, philo, arr[i]);
		pthread_detach((arr[0])->id[i]);
		i++;
	}
	
	watch_philo(arr);
	
	free(arr[0]->id);
	i = 0;
	while (i < arr[0]->nbr_phil)
	{
		pthread_mutex_destroy(&arr[0]->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&arr[0]->print);
	
}

void	assign_philo(t_philo	**arr, t_philo	*phil, int i)
{
	arr[i]->ac = phil->ac;
	arr[i]->nbr_phil = phil->nbr_phil;
	arr[i]->t_to_die = 1000 * phil->t_to_die;
	arr[i]->t_to_eat = 1000 * phil->t_to_eat;
	arr[i]->t_to_slp = 1000 * phil->t_to_slp;
	if (phil->ac == 6)
	{
		arr[i]->must_eat = phil->must_eat;
		arr[i]->has_eatn = 0;
	}
	arr[i]->id = phil->id;
	arr[i]->mutex = phil->mutex;
	arr[i]->philo = phil;
	arr[i]->x_phil = i;
	arr[i]->left = i;
	arr[i]->right = i + 1;
	if (i == phil->nbr_phil - 1)
		arr[i]->right = 0;
}

int	init_philo_2(t_philo	**arr, t_philo	*phil)
{
	int		i;

	phil->id = (pthread_t *)malloc(sizeof(pthread_t) * phil->nbr_phil);
	if (phil->id == NULL)
		return (2);
	phil->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* phil->nbr_phil);
	if (phil->mutex == NULL)
		return (2);
	i = 0;
	while (i < phil->nbr_phil)
	{
		pthread_mutex_init(&phil->mutex[i], 0);
		i++;
	}
	//отсюда ниже проблемы
	arr[0] = phil;
	i = 1;
	while (i < phil->nbr_phil)
	{
		arr[i] = (t_philo	*)malloc(sizeof(t_philo));
		if (arr[i] == NULL)
			return (free_arr(arr, i));
		assign_philo(arr, phil, i);
		i++;
	}
	return (0);
}

int	init_philo(t_philo	**arr, int ac, char	**av)
{
	t_philo	*phil;

	phil = (t_philo *)malloc(sizeof(t_philo) * 1);
	if (phil == NULL)
		return (2);
	// phil->x_phil = 1;
	gettimeofday(&phil->start, 0);
	//перетащить ближе к осн операциям
	phil->ac = ac;
	phil->nbr_phil = ft_atoi(av[1]);
	phil->t_to_die = ft_atoi(av[2]);
	phil->t_to_eat = ft_atoi(av[3]);
	phil->t_to_slp = ft_atoi(av[4]);
	phil->philo = phil;
	//?
	if (phil->ac == 6)
		phil->must_eat = ft_atoi(av[5]);
	if (init_philo_2(arr, phil))
		return (2);
	pthread_mutex_init(&phil->print, 0);
	start_philo(arr);
	return (0);
}

int	main(int ac, char	**av)
{
	t_philo	**arr;
	int		ret;

	if (ac != 5 && ac != 6)
	{
		printf("Error:\nInvalid arguments\n");
		return (1);
	}
	arr = (t_philo **)malloc(sizeof(t_philo *) * ft_atoi(av[1]));
	if (!arr)
		return (2);
	ret = init_philo(arr, ac, av);
	return (ret);
}
