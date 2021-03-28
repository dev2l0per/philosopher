/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:24:32 by juyang            #+#    #+#             */
/*   Updated: 2021/03/28 16:24:34 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void				*full_check(void *arg)
{
	t_prog			*prog;
	int				i;
	int				full_cnt;

	prog = (t_prog *)arg;
	full_cnt = 0;
	i = -1;
	while (1)
	{
		sem_wait(prog->system.status);
		full_cnt++;
		if (full_cnt == prog->system.number_of_philosophers)
		{
			prog->philo[i].status = FULL;
			printf("All Philosophers are full\n");
			sem_post(prog->system.finish_check);
			break ;
		}
		usleep(50);
	}
	return (NULL);
}

void				*death_check(void *arg)
{
	t_philosopher			*philo;

	philo = (t_philosopher *)arg;
	while (philo->status == ALIVE)
	{
		if ((get_time() - philo->last_eat) > philo->time_to_die)
		{
			print_state(" is Died", philo);
			philo->status = DIED;
			sem_post(philo->prog_ptr->system.finish_check);
		}
		usleep(50);
	}
	return (NULL);
}

void				wait_time(long long int save, long long int time_to)
{
	long long int	wait;

	while (get_time() < (save + time_to))
	{
		wait = (save + time_to - get_time()) * 1000 / 2;
		usleep(wait);
	}
}

void				*finish_check(void *arg)
{
	t_prog			*prog;
	int				i;

	i = -1;
	prog = (t_prog *)arg;
	sem_wait(prog->system.finish_check);
	while (++i < prog->system.number_of_philosophers)
		kill(prog->philo[i].pid, SIGKILL);
	return ((void *)NULL);
}
