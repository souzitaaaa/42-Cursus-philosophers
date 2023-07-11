/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:17:26 by dinoguei          #+#    #+#             */
/*   Updated: 2023/07/11 15:42:40 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_main *main)
{
	int		i;

	i = 0;
	while (i < main->n_philos)
	{
		pthread_mutex_init(&main->fork[i], NULL);
		i++;
	}
	if (main->n_philos > 1)
	{
		main->philo[0].left_chop_mut = &main->fork[0];
		main->philo[0].right_chop_mut = &main->fork[main->n_philos - 1];
	}
	else
		main->philo[0].left_chop_mut = &main->fork[0];
	i = 1;
	while (i < main->n_philos)
	{
		main->philo[i].left_chop_mut = &main->fork[i];
		main->philo[i].right_chop_mut = &main->fork[i - 1];
		i++;
	}
}

void	init_philo(t_main *main)
{
	int		i;
	int		times;

	times = 0;
	i = 0;
	while (i < main->n_philos)
	{
		main->philo[i].main = main;
		main->philo[i].id = i + 1;
		main->philo[i].state = WAITING;
		main->philo[i].left_chopstick = i;
		if (times == 0)
			main->philo[i].right_chopstick = main->n_philos - 1;
		else
			main->philo[i].right_chopstick = i - 1;
		main->philo[i].times_eaten = 0;
		pthread_mutex_init(&main->philo[i].last_eat_mut, NULL);
		pthread_mutex_init(&main->philo[i].state_mut, NULL);
		pthread_mutex_init(&main->philo[i].times_eaten_mut, NULL);
		set_last_eat_time(&main->philo[i]);
		times++;
		i++;
	}
}

void	init_mallocs(t_main *main)
{
	main->philo = malloc(sizeof(t_philo) * main->n_philos);
	if (!main->philo)
		exit(1);
	main->fork = malloc(sizeof(pthread_mutex_t) * main->n_philos);
	if (!main->fork)
		exit(1);
	main->thread = malloc(sizeof(pthread_t) * main->n_philos);
	if (!main->thread)
		exit(1);
}

void	init_mutexes(t_main *main)
{
	pthread_mutex_init(&main->eat_mut, NULL);
	pthread_mutex_init(&main->die_mut, NULL);
	pthread_mutex_init(&main->print_mut, NULL);
	pthread_mutex_init(&main->running_mut, NULL);
}

void	init_struct(char **argv, t_main *main)
{
	main->n_philos = ft_atoi(argv[1]);
	main->time_die = ft_atoi(argv[2]);
	main->time_eat = ft_atoi(argv[3]);
	main->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		main->times_must_eat = ft_atoi(argv[5]);
		main->must_eat = true;
	}
	else
	{
		main->times_must_eat = -1;
		main->must_eat = false;
	}
	if (main->times_must_eat == 0)
	{
		printf("Philosophers need to eat at least one time\n");
		exit(EXIT_FAILURE);
	}
	main->running = true;
	init_mallocs(main);
	init_mutexes(main);
}
