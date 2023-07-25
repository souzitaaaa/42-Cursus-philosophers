/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:27:21 by dinoguei          #+#    #+#             */
/*   Updated: 2023/07/25 12:57:30 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <strings.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_main	t_main;

typedef enum state
{
	EATING = 0,
	THINKING = 1,
	SLEEPING = 2,
	DEAD = 3,
	WAITING = 4,
}	t_state;

typedef struct s_philo
{
	t_main			*main;
	int				id;
	int				right_chopstick;
	int				left_chopstick;
	int				times_eaten;
	long int		time_last_eat;
	bool			first_routine;
	pthread_mutex_t	*right_chop_mut;
	pthread_mutex_t	*left_chop_mut;
	pthread_mutex_t	state_mut;
	pthread_mutex_t	last_eat_mut;
	pthread_mutex_t	times_eaten_mut;
	t_state			state;
}	t_philo;

typedef struct s_main
{
	t_philo			*philo;
	bool			running;
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_must_eat;
	bool			must_eat;
	long long int	time_started;
	pthread_mutex_t	*fork;
	pthread_mutex_t	running_mut;
	pthread_mutex_t	eat_mut;
	pthread_mutex_t	die_mut;
	pthread_mutex_t	print_mut;
	pthread_t		*thread;
	pthread_t		check_full;
	pthread_t		check_dead;
}	t_main;

/*
main.c
*/
int			main(int argc, char **argv);
void		destroy(t_main *main);
/*
args.c
*/
bool		check_num(int digit);
bool		check_numerical(char **str);
void		check_arg(int argc, char **argv);
/*
init.c
*/
void		init_struct(char **argv, t_main *philo);
void		init_mutexes(t_main *philo);
void		init_mallocs(t_main *philo);
void		init_philo(t_main *philo);
void		init_forks(t_main *philo);
/*
threads.c
*/
void		start_threads(t_main *philo);
void		join_threads(t_main *main);
/*
routine.c
*/
void		*routine(void *arg);
void		*check_full(void *arg);
void		*check_dead(void *arg);
void		check_if_first(t_philo *philo);
/*
eat.c
*/
int			eat(t_philo *philo);
void		drop_chops(t_philo *philo);
int			get_chops(t_philo *philo);
int			take_left_chop(t_philo *philo);
int			take_right_chop(t_philo *philo);
/*
utils.c
*/
int			ft_atoi(char *str);
void		print_philo(t_philo *philo, int id, char *msg);
uint64_t	gettime(void);
int			get_times_eaten(t_philo *philo);
/*
utils2.c
*/
void		set_last_eat_time(t_philo *philo);
void		time_sleep(t_philo *philo, int state);
int			philo_get_state(t_philo *philo);
void		set_state(t_philo *philo, int state);
bool		get_running(t_main *main);
void		set_running(t_main *main, bool state);
/*
sleep_think.c
*/
int			sleep_philo(t_philo *philo);
int			think(t_philo *philo);
/*
utils3.c
*/
void		stop_all(t_main *main);
bool		check_full_philos(t_philo *philo);
bool		check_dead_philos(t_philo *philo);
int			handle_one(t_philo *philo);
long int	get_last_eat_time(t_philo *philo);

#endif