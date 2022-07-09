/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:26:57 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/09 21:03:18 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	char			**av;
	int				y;
	int				ac;
	int				x_phil;
	int				left;
	int				right;
	int				to_end;
	int				nbr_phil;
	int				must_eat;
	int				has_eatn;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_slp;
	pthread_t		*id;
	pthread_mutex_t	print;
	pthread_mutex_t	is_ded;
	pthread_mutex_t	*mutex;
	struct s_philo	*philo;
	struct timeval	start;
	struct timeval	last_fed;
}	t_philo;

int		ft_atoi(const char	*str);
void	start_philo(t_philo	*arr);
void	watch_philo(t_philo	*arr);
void	*philo(void	*phil);
int		munch(t_philo	*p, struct timeval *now);
void	time_to_sleep(t_philo	*p, struct timeval *now);
void	sleeping(long millisec);
int		number_fed(t_philo	*p);
int		get_time(struct timeval *now, t_philo	*p, int x);
int		meal_count(t_philo	*arr, int y);
void	fork_unlock(t_philo	*p);
void	is_dead(t_philo	*arr, struct timeval *now, int i);

#endif