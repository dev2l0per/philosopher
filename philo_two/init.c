/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:29:32 by juyang            #+#    #+#             */
/*   Updated: 2021/03/28 14:29:32 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int					semaphore_init(t_prog *prog)
{
	sem_unlink("/forks");
	sem_unlink("/status");
	sem_unlink("/write");
	sem_unlink("/finish_check");
	prog->system.forks = sem_open("/forks",
	O_CREAT, 0644, prog->system.number_of_philosophers);
	if (prog->system.forks == SEM_FAILED)
		return (-1);
	prog->system.status = sem_open("/status", O_CREAT, 0644, 1);
	if (prog->system.status == SEM_FAILED)
		return (-1);
	prog->system.write = sem_open("/write", O_CREAT, 0644, 1);
	if (prog->system.write == SEM_FAILED)
		return (-1);
	prog->system.finish_check = sem_open("/finish_check", O_CREAT, 0644, 1);
	if (prog->system.finish_check == SEM_FAILED)
		return (-1);
	return (0);
}

void				philosopher_init(t_prog *prog)
{
	int				i;

	i = 0;
	while (i < prog->system.number_of_philosophers)
	{
		prog->philo[i].left_fork = prog->system.forks;
		prog->philo[i].right_fork = prog->system.forks;
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
	if (prog->system.number_of_philosophers < 2)
		return (-1);
	prog->system.number_of_times_each_philosopher_must_eat = 0;
	if (argc == 6)
		prog->system.number_of_times_each_philosopher_must_eat =
		ft_atoi(argv[5]);
	prog->philo = (t_philosopher *)malloc(sizeof(t_philosopher)
	* prog->system.number_of_philosophers);
	if (!prog->philo)
		return (-1);
	i = -1;
	while (++i < prog->system.number_of_philosophers)
	{
		prog->philo[i].time_to_die = ft_atoi(argv[2]);
		prog->philo[i].time_to_eat = ft_atoi(argv[3]);
		prog->philo[i].time_to_sleep = ft_atoi(argv[4]);
		prog->philo[i].prog_ptr = prog;
	}
	return (0);
}
