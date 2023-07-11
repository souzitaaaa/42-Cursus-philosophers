/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:18:48 by dinoguei          #+#    #+#             */
/*   Updated: 2023/07/11 16:11:33 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_full_philos(t_philo *philo)
{
	int		times_eaten;

	times_eaten = get_times_eaten(philo);
	if (times_eaten < philo->main->times_must_eat)
		return (false);
	else
		return (true);
}

bool	check_dead_philos(t_philo *philo)
{
	if (gettime() - get_last_eat_time(philo)
		> (unsigned long)philo->main->time_die
		&& philo_get_state(philo) != EATING)
	{
		set_state(philo, DEAD);
		return (true);
	}
	return (false);
}

void	stop_all(t_main *main)
{
	int		i;

	i = 0;
	while (i < main->n_philos)
	{
		set_state(&main->philo[i], DEAD);
		i++;
	}
}

int	handle_one(t_philo *philo)
{
	take_left_chop(philo);
	pthread_mutex_unlock(philo->left_chop_mut);
	time_sleep(philo, DEAD);
	set_state(philo, DEAD);
	return (0);
}

long int	get_last_eat_time(t_philo *philo)
{
	long int	time;

	time = 0;
	pthread_mutex_lock(&philo->last_eat_mut);
	time = philo->time_last_eat;
	pthread_mutex_unlock(&philo->last_eat_mut);
	return (time);
}
