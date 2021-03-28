/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:29:46 by juyang            #+#    #+#             */
/*   Updated: 2021/03/28 14:29:47 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void				*full_check(void *arg)
{
	t_prog			*prog;
	int				i;
	int				full_cnt;

	prog = (t_prog *)arg;
	full_cnt = 0;
	while (1)
	{
		i = -1;
		while (++i < prog->system.number_of_philosophers)
			if (prog->philo[i].status == ALIVE && prog->philo[i].eat_cnt
			>= prog->system.number_of_times_each_philosopher_must_eat
			&& prog->system.number_of_times_each_philosopher_must_eat)
			{
				sem_wait(prog->system.status);
				prog->philo[i].status = FULL;
				sem_post(prog->system.status);
				full_cnt++;
				break ;
			}
		if (full_cnt_check(prog, full_cnt) == 1)
			break ;
		usleep(50);
	}
	return (NULL);
}

int					full_cnt_check(t_prog *prog, int full_cnt)
{
	if (full_cnt == prog->system.number_of_philosophers)
	{
		prog->system.finish = 1;
		sem_wait(prog->system.write);
		printf("All Philosophers is Full\n");
		sem_post(prog->system.write);
		return (1);
	}
	return (0);
}

void				*death_check(void *arg)
{
	t_philosopher			*philo;

	philo = (t_philosopher *)arg;
	while (philo->status == ALIVE)
	{
		sem_wait(philo->prog_ptr->system.finish_check);
		if ((get_time() - philo->last_eat) > philo->time_to_die
		&& philo->prog_ptr->system.finish == 0)
		{
			philo->prog_ptr->system.finish = 1;
			sem_wait(philo->prog_ptr->system.status);
			philo->status = DIED;
			sem_post(philo->prog_ptr->system.status);
			print_state("is Died", philo);
		}
		sem_post(philo->prog_ptr->system.finish_check);
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
