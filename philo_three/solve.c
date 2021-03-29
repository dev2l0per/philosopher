/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:24:42 by juyang            #+#    #+#             */
/*   Updated: 2021/03/28 16:24:44 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void				take_fork(t_philosopher *philo)
{
	sem_wait(philo->left_fork);
	sem_wait(philo->right_fork);
	if (philo->status != DIED && philo->status != FULL)
		print_state(" has taken a fork", philo);
}

void				sleeping(t_philosopher *philo)
{
	if (philo->prog_ptr->system.number_of_times_each_philosopher_must_eat
	&& philo->eat_cnt >=
	philo->prog_ptr->system.number_of_times_each_philosopher_must_eat)
	{
		philo->status = FULL;
		sem_post(philo->left_fork);
		sem_post(philo->right_fork);
		sem_post(philo->prog_ptr->system.status);
		return ;
	}
	if (philo->status != DIED && philo->status != FULL)
	{
		print_state(" is Sleeping", philo);
		wait_time(get_time(), philo->time_to_sleep);
	}
}

void				eating(t_philosopher *philo)
{
	if (philo->status != DIED && philo->status != FULL)
	{
		philo->last_eat = get_time();
		print_state(" is Eating", philo);
		wait_time(philo->last_eat, philo->time_to_eat);
		philo->eat_cnt++;
		sem_post(philo->left_fork);
		sem_post(philo->right_fork);
	}
	else
	{
		sem_post(philo->left_fork);
		sem_post(philo->right_fork);
	}
}

void				solve(void *arg)
{
	t_philosopher	*philo;
	pthread_t		died_check;

	philo = (t_philosopher *)arg;
	philo->last_eat = get_time();
	pthread_create(&died_check, NULL, death_check, (void *)philo);
	pthread_detach(died_check);
	if (philo->index % 2 != 0)
		wait_time(get_time(), philo->time_to_eat);
	while (philo->status != DIED && philo->status != FULL)
	{
		take_fork(philo);
		eating(philo);
		sleeping(philo);
		if (philo->status != DIED && philo->status != FULL)
			print_state(" is Thinking", philo);
		usleep(50);
	}
}
