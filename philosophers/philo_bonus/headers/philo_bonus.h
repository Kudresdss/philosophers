/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 20:35:32 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/09 18:38:43 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <semaphore.h>

typedef struct s_philo
{
	char			**av;
	int				ac;
	int				dead;
	int				status;
	int				to_end;
	int				x_phil;
	int				x_to_end;
	int				nbr_phil;
	int				must_eat;
	int				has_eatn;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_slp;
	pid_t			*pid;
	sem_t			*sem;
	sem_t			*print;
	sem_t			*is_dead;
	struct timeval	start;
	struct timeval	last_fed;
}	t_philo;

int		start_philo(t_philo	*phil);
void	philo(t_philo	*phil, int i);
void	philo_slp_and_thnk(t_philo	*phil, struct timeval *now);
void	philo_forks(t_philo	*phil, struct timeval *now);
void	*watch_philo(void	*p);
int		init_philo(t_philo	*phil, int ac, char	**av);
int		init_2(t_philo	*phil);
int		init_pid(t_philo	*phil);
void	clean_all(t_philo	*phil);
void	to_close_sem(t_philo	*phil);
int		ft_atoi(const char	*str);
void	sleeping(long microsec);
int		get_time(struct timeval *now, t_philo	*p, int x);

#endif
