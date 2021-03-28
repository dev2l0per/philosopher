/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:20:29 by juyang            #+#    #+#             */
/*   Updated: 2021/03/23 16:20:30 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				mutex_init(t_prog *prog)
{
	int				i;

	i = 0;
	while (i < prog->system.number_of_philosophers)
		pthread_mutex_init(&prog->system.forks[i++], NULL);
	pthread_mutex_init(&prog->system.status, NULL);
	pthread_mutex_init(&prog->system.write, NULL);
	pthread_mutex_init(&prog->system.finish_check, NULL);
}

void				philosopher_init(t_prog *prog)
{
	int				i;

	i = 0;
	while (i < prog->system.number_of_philosophers)
	{
		if (i == 0)
			prog->philo[i].left_fork = &prog->system.forks[prog->system.number_of_philosophers - 1];
		else
			prog->philo[i].left_fork = &prog->system.forks[i - 1];
		prog->philo[i].right_fork = &prog->system.forks[i];
		prog->philo[i].index = i + 1;
		prog->philo[i].eat_cnt = 0;
		prog->philo[i].status = ALIVE;
		i++;
	}
}

int					argument_init(t_prog *prog, int argc, char **argv)
{
	int				i;

	prog->system.number_of_philosophers = ft_atoi(argv[1]);
		prog->system.number_of_times_each_philosopher_must_eat = 0;
		if (argc == 6)
			prog->system.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	prog->philo = (t_philosopher *)malloc(sizeof(t_philosopher) * prog->system.number_of_philosophers);
	if (!prog->philo)
	{
		write(1, "Philosopher Allocate Error\n", 27);
		return (-1);
	}
	i = 0;
	while (i < prog->system.number_of_philosophers)
	{
		prog->philo[i].time_to_die = ft_atoi(argv[2]);
		prog->philo[i].time_to_eat = ft_atoi(argv[3]);
		prog->philo[i].time_to_sleep = ft_atoi(argv[4]);
		prog->philo[i].prog_ptr = prog;
		i++;
	}
	prog->system.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * prog->system.number_of_philosophers);
	if (!prog->system.forks)
	{
		write(1, "Forks Allocate Error\n", 21);
		return (-1);
	}
	return (0);
}
