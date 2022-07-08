/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 20:02:14 by ymirna            #+#    #+#             */
/*   Updated: 2022/07/08 07:49:42 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo_bonus.h"

void	saturation_of_hunger(t_philo	*phil)
{
	sem_wait(phil->print);
	printf("Philosophical hunger has been sated %d times\n",
		phil->must_eat);
	clean_all(phil);
}

int	end_philo(t_philo	*phil, int i)
{
	while (i < phil->nbr_phil)
	{
		waitpid(-1, &phil->status, 0);
		if (WIFEXITED(phil->status))
		{
			phil->status = WEXITSTATUS(phil->status);
			if (phil->status == 1)
			{
				clean_all(phil);
				break ;
			}
			else if (phil->status == 2)
			{
				phil->x_to_end++;
				if (phil->x_to_end == phil->nbr_phil)
				{
					saturation_of_hunger(phil);
					break ;
				}
			}
		}
		i++;
	}
	return (0);
}

int	start_philo(t_philo	*phil)
{
	int		i;

	i = 0;
	if (init_pid(phil))
		return (6);
	gettimeofday(&phil->start, 0);
	while (i < phil->nbr_phil)
	{
		phil->pid[i] = fork();
		if (!phil->pid[i])
			philo(phil, i + 1);
		else if (phil->pid[i] < 0)
			return (4);
		else
			i++;
	}
	i = 0;
	return (end_philo(phil, i));
}

int	main(int ac, char	**av)
{
	t_philo	phil;
	int		ret;

	if (ac != 5 && ac != 6)
	{
		write(2, "Error:\nInvalid number of arguments\n", 36);
		return (1);
	}
	ret = init_philo(&phil, ac, av);
	if (ret == 2)
		write(2, "Invalid argument values\n", 24);
	else if (ret == 3)
		write(2, "Too many philosophers\n", 22);
	else if (ret == 4)
	{
		to_close_sem(&phil);
		write(2, "Fork error\n", 11);
	}
	return (ret);
}
