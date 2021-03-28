/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:03:37 by juyang            #+#    #+#             */
/*   Updated: 2021/03/23 17:03:38 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
			> prog->system.number_of_times_each_philosopher_must_eat 
			&& prog->system.number_of_times_each_philosopher_must_eat)
			{
				pthread_mutex_lock(&prog->philo[i].prog_ptr->system.status);
				prog->philo[i].status = FULL;
				pthread_mutex_unlock(&prog->system.status);
				full_cnt++;
				break ;
			}
		if (full_cnt == prog->system.number_of_philosophers)
		{
			prog->system.finish = 1;
			pthread_mutex_lock(&prog->system.write);
			printf("All Philosophers is Full\n");
			pthread_mutex_unlock(&prog->system.write);
			break ;
		}
	}
	return (NULL);
}

void				*death_check(void *arg)
{
	t_philosopher			*philo;
	long long int			a;

	philo = (t_philosopher *)arg;
	while (philo->status == ALIVE)
	{
		pthread_mutex_lock(&philo->prog_ptr->system.finish_check);
		if ((a = get_time() - philo->last_eat) > philo->time_to_die && philo->prog_ptr->system.finish == 0)
		{
			printf("%lld\n", a);
			philo->prog_ptr->system.finish = 1;
			pthread_mutex_lock(&philo->prog_ptr->system.status);
			philo->status = DIED;
			pthread_mutex_unlock(&philo->prog_ptr->system.status);
			print_state("is Died", philo);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		pthread_mutex_unlock(&philo->prog_ptr->system.finish_check);
	}
	return (NULL);
}
