/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:15:24 by dinoguei          #+#    #+#             */
/*   Updated: 2023/06/27 16:15:24 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_main *main)
{
	int		i;

	i = 0;
	main->time_started = gettime();
	while (i < main->n_philos)
	{
		pthread_create(&main->thread[i], NULL, &routine, &main->philo[i]);
		i++;
	}
	pthread_create(&main->check_dead, NULL, &check_dead, main);
	if (main->must_eat == true)
		pthread_create(&main->check_full, NULL, &check_full, main);
}

void	join_threads(t_main *main)
{
	int		i;

	i = 0;
	while (i < main->n_philos)
	{
		pthread_join(main->thread[i], NULL);
		i++;
	}
	pthread_join(main->check_dead, NULL);
	if (main->must_eat == true)
		pthread_join(main->check_full, NULL);
}
