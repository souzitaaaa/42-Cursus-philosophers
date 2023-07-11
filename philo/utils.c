/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:48:16 by dinoguei          #+#    #+#             */
/*   Updated: 2023/07/11 16:21:12 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		sign;
	int		out;
	int		i;

	sign = 1;
	out = 0;
	i = 0;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		out = out * 10 + str[i] - '0';
		i++;
	}
	return (out * sign);
}

void	print_philo(t_philo *philo, int id, char *msg)
{
	long long int	time;
	static bool		first_dead = false;

	time = 0;
	if (philo_get_state(philo) == DEAD || check_dead_philos(philo))
	{
		if (first_dead == false)
			first_dead = true;
		else
			return ;
	}
	time = gettime() - philo->main->time_started;
	pthread_mutex_lock(&philo->main->print_mut);
	printf("%llu %i %s\n", time, id, msg);
	pthread_mutex_unlock(&philo->main->print_mut);
}

uint64_t	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	time_sleep(t_philo *philo, int state)
{
	if (state == EATING)
		usleep(philo->main->time_eat * 1000);
	else if (state == SLEEPING)
		usleep(philo->main->time_sleep * 1000);
	else if (state == DEAD)
		usleep(philo->main->time_die * 1000);
}

int	get_times_eaten(t_philo *philo)
{
	int		out;

	out = 0;
	pthread_mutex_lock(&philo->times_eaten_mut);
	out = philo->times_eaten;
	pthread_mutex_unlock(&philo->times_eaten_mut);
	return (out);
}
