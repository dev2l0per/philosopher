/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:36:24 by juyang            #+#    #+#             */
/*   Updated: 2021/03/23 16:36:25 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				take_fork(t_philosopher *philo)
{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	if (philo->prog_ptr->system.finish == 0)
		print_state("has taken a fork", philo);
}

void				sleeping(t_philosopher *philo)
{
	if (philo->prog_ptr->system.finish == 0)
	{
		print_state("is Sleeping", philo);
		usleep(philo->time_to_sleep * 1000);
	}
}

void				eating(t_philosopher *philo)
{
	if (philo->prog_ptr->system.finish == 0)
	{
		philo->last_eat = get_time();
		print_state("is Eating", philo);
		usleep(philo->time_to_eat * 1000);
		philo->eat_cnt++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void				*solve(void *arg)
{
	t_philosopher	*philo;
	pthread_t		died_check;

	philo = (t_philosopher *)arg;
	philo->last_eat = get_time();
	pthread_create(&died_check, NULL, death_check, (void *)philo);
	pthread_detach(died_check);
	if (philo->index % 2 == 0)
		usleep(philo->time_to_eat * 1000);
	while (philo->prog_ptr->system.finish == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		if (philo->prog_ptr->system.finish == 0)
			print_state("has taken a fork", philo);
		eating(philo);
		if (philo->prog_ptr->system.finish == 0)
		{
			print_state("is Sleeping", philo);
			print_state("is Thinking", philo);
			usleep(philo->time_to_sleep * 1000);
		}
		// if (philo->prog_ptr->system.finish == 0)
	}
	return (NULL);
}
