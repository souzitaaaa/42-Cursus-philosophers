/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:34:18 by dinoguei          #+#    #+#             */
/*   Updated: 2023/07/11 16:20:46 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_mut);
	philo->time_last_eat = gettime();
	pthread_mutex_unlock(&philo->last_eat_mut);
}

void	set_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->state_mut);
	if (philo->state != DEAD)
		philo->state = state;
	pthread_mutex_unlock(&philo->state_mut);
}

int	philo_get_state(t_philo *philo)
{
	int		state;

	state = 0;
	pthread_mutex_lock(&philo->state_mut);
	state = philo->state;
	pthread_mutex_unlock(&philo->state_mut);
	return (state);
}

bool	get_running(t_main *main)
{
	bool	out;

	out = true;
	pthread_mutex_lock(&main->running_mut);
	out = main->running;
	pthread_mutex_unlock(&main->running_mut);
	return (out);
}

void	set_running(t_main *main, bool state)
{
	pthread_mutex_lock(&main->running_mut);
	main->running = state;
	pthread_mutex_unlock(&main->running_mut);
}
