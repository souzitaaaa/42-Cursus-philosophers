/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:33:18 by dinoguei          #+#    #+#             */
/*   Updated: 2023/07/26 14:34:02 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
void print_philos(t_main *philo)
{
	int i = 0;

	printf("\033[1;33m\n\n    General Information\033[0m\n");
	printf("\033[1;33mN_philos:\033[0m %i\n", philo->n_philos);
	printf("\033[1;33mTime to die:\033[0m %i\n", philo->time_die);
	printf("\033[1;33mTime to eat:\033[0m %i\n", philo->time_eat);
	printf("\033[1;33mTime to sleep:\033[0m %i\n", philo->time_sleep);
	if(philo->times_must_eat != -1)
		printf("\033[1;33mTimes must eat:\033[0m %i\n", philo->times_must_eat);
	while (i < philo->n_philos)
	{
		printf("\033[1;31m\tPHILO %i\033[0m\n", philo->philo[i].id + 1);
		printf("\033[1;32mState:\033[0m %i\n", philo->philo[i].state);
		printf("\033[1;32mLeft chop:\033[0m %i\n", philo->philo[i].left_chopstick);
		printf("\033[1;32mRight chop:\033[0m %i\n", philo->philo[i].right_chopstick);
		printf("\033[1;32mLast eaten:\033[0m %li\n", philo->philo[i].time_last_eat);
		printf("\033[1;32mTimes eaten:\033[0m %i\n", philo->philo[i].times_eaten);
		i++;
	}
}*/
void	destroy(t_main *main)
{
	int		i;

	i = 0;
	while (i < main->n_philos)
	{
		pthread_mutex_destroy(&main->fork[i]);
		pthread_mutex_destroy(&main->philo[i].last_eat_mut);
		pthread_mutex_destroy(&main->philo[i].state_mut);
		pthread_mutex_destroy(&main->philo[i].times_eaten_mut);
		pthread_mutex_destroy(main->philo[i].left_chop_mut);
		if (main->n_philos > 1)
			pthread_mutex_destroy(main->philo[i].right_chop_mut);
		i++;
	}
	pthread_mutex_destroy(&main->eat_mut);
	pthread_mutex_destroy(&main->die_mut);
	pthread_mutex_destroy(&main->print_mut);
	pthread_mutex_destroy(&main->running_mut);
	free(main->philo);
	free(main->fork);
	free(main->thread);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (check_arg(argc, argv) == 1)
		return (0);
	if (init_struct(argv, &main) == 1)
		return (0);
	init_philo(&main);
	init_forks(&main);
	start_threads(&main);
	join_threads(&main);
	destroy(&main);
	return (0);
}
