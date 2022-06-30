/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:26:57 by ymirna            #+#    #+#             */
/*   Updated: 2022/06/29 11:44:09 by ymirna           ###   ########.fr       */
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
	int				ac;
	int				x_phil;
	int				left;
	int				right;
	int				nbr_phil;
	int				must_eat;
	int				has_eatn;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_slp;
	pthread_t		*id;
	pthread_mutex_t	print;
	pthread_mutex_t	full;
	pthread_mutex_t	*mutex;
	struct s_philo	*philo;
	struct timeval	start;
	struct timeval	last_fed;
}	t_philo;

int		ft_atoi(const char	*str);
int		free_arr(t_philo	**arr, int i);
void	sleeping(long sec);
int		get_time(struct timeval *now, t_philo	*p);

#endif