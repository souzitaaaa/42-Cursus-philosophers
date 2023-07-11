/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:06:24 by dinoguei          #+#    #+#             */
/*   Updated: 2023/06/27 19:06:24 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_philo(t_philo *philo)
{
	set_state(philo, SLEEPING);
	if (philo_get_state(philo) == DEAD || check_dead_philos(philo))
		return (0);
	print_philo(philo, philo->id, "is sleeping");
	time_sleep(philo, SLEEPING);
	return (1);
}

int	think(t_philo *philo)
{
	set_state(philo, THINKING || check_dead_philos(philo));
	if (philo_get_state(philo) == DEAD)
		return (0);
	print_philo(philo, philo->id, "is thinking");
	return (1);
}
