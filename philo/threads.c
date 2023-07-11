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
		if (pthread_create(&main->thread[i], NULL, &routine, &main->philo[i]))
			exit(1);
		i++;
	}
	if (pthread_create(&main->check_dead, NULL, &check_dead, main))
		exit(1);
	if (main->must_eat == true)
	{
		if (pthread_create(&main->check_full, NULL, &check_full, main))
			exit(1);
	}
}

void	join_threads(t_main *main)
{
	int		i;

	i = 0;
	while (i < main->n_philos)
	{
		if (pthread_join(main->thread[i], NULL) != 0)
			exit(1);
		i++;
	}
	if (pthread_join(main->check_dead, NULL) != 0)
		exit(1);
	if (main->must_eat == true
		&& pthread_join(main->check_full, NULL) != 0)
		exit(1);
}
