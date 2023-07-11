/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:19:53 by dinoguei          #+#    #+#             */
/*   Updated: 2023/07/11 16:18:45 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		set_last_eat_time(philo);
	while (philo_get_state(philo) != DEAD)
	{
		if (philo->id % 2 != 0)
		{
			usleep((philo->main->time_eat / 25) * 1000);
			set_last_eat_time(philo);
		}
		if (eat(philo) == 0)
			break ;
		if (philo_get_state(philo) == DEAD)
			break ;
		if (sleep_philo(philo) == 0)
			break ;
		if (philo_get_state(philo) == DEAD)
			break ;
		if (think(philo) == 0)
			break ;
	}
	return (NULL);
}

void	*check_full(void *arg)
{
	t_main	*main;
	int		i;

	i = -1;
	main = (t_main *)arg;
	while (i++ < main->n_philos && get_running(main))
	{
		if (!(check_full_philos(&main->philo[i])))
			i = -1;
		if (i == main->n_philos - 1)
		{
			stop_all(main);
			set_running(main, false);
			break ;
		}
	}
	return (NULL);
}

void	*check_dead(void *arg)
{
	t_main	*main;
	int		i;

	i = 0;
	main = (t_main *)arg;
	while (i < main->n_philos && get_running(main))
	{
		if (check_dead_philos(&main->philo[i]))
		{
			print_philo(&main->philo[i], main->philo[i].id, "died");
			set_running(main, false);
			stop_all(main);
			break ;
		}
		i++;
		if (i == main->n_philos)
			i = 0;
	}
	return (NULL);
}
