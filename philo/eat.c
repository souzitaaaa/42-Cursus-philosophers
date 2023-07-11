/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:55:48 by dinoguei          #+#    #+#             */
/*   Updated: 2023/06/27 18:55:48 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_right_chop(t_philo *philo)
{
	if (philo_get_state(philo) == DEAD || check_dead_philos(philo))
		return (0);
	pthread_mutex_lock(philo->right_chop_mut);
	print_philo(philo, philo->id, "has taken a fork");
	return (1);
}

int	take_left_chop(t_philo *philo)
{
	if (philo_get_state(philo) == DEAD || check_dead_philos(philo))
		return (0);
	pthread_mutex_lock(philo->left_chop_mut);
	print_philo(philo, philo->id, "has taken a fork");
	return (1);
}

int	get_chops(t_philo *philo)
{
	if (philo->main->n_philos == 1)
		return (handle_one(philo));
	if (philo->id % 2 != 0)
	{
		if (take_right_chop(philo) == 0)
			return (0);
		if (take_left_chop(philo) == 0)
		{
			pthread_mutex_unlock(philo->right_chop_mut);
			return (0);
		}
	}
	else
	{
		if (take_left_chop(philo) == 0)
			return (0);
		if (take_right_chop(philo) == 0)
		{
			pthread_mutex_unlock(philo->left_chop_mut);
			return (0);
		}
	}
	return (1);
}

void	drop_chops(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_chop_mut);
	pthread_mutex_unlock(philo->left_chop_mut);
}

int	eat(t_philo *philo)
{
	if (get_chops(philo) == 0)
		return (0);
	set_state(philo, EATING);
	print_philo(philo, philo->id, "is eating");
	set_last_eat_time(philo);
	time_sleep(philo, EATING);
	pthread_mutex_lock(&philo->times_eaten_mut);
	philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->times_eaten_mut);
	drop_chops(philo);
	return (1);
}
