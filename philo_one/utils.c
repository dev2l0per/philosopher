/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:32:39 by juyang            #+#    #+#             */
/*   Updated: 2021/03/23 16:32:39 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long long int		get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

int					ft_atoi(const char *str)
{
	long long int	res;
	long long int	sign;

	res = 0;
	sign = 1;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res > 2147483647 && sign == 1)
			return (-1);
		if (res > 2147483648 && sign == -1)
			return (0);
		str++;
	}
	return (sign * res);
}

void				print_state(char *str, t_philosopher *philo)
{
	if (philo->status != DIED && philo->status != FULL && philo->prog_ptr->system.finish == 0)
	{
		pthread_mutex_lock(&philo->prog_ptr->system.write);
		printf("%lldms %d ", get_time() - philo->prog_ptr->system.start_time, philo->index);
		printf("%s\n", str);
		pthread_mutex_unlock(&philo->prog_ptr->system.write);
	}
	else if (philo->status == DIED)
	{
		pthread_mutex_lock(&philo->prog_ptr->system.write);
		printf("%lldms %d ", get_time() - philo->prog_ptr->system.start_time, philo->index);
		printf("%s\n", str);
		pthread_mutex_unlock(&philo->prog_ptr->system.write);
	}
}

void				clear(t_prog *prog)
{
	int			i;

	i = -1;
	while (++i < prog->system.number_of_philosophers)
		pthread_mutex_destroy(&prog->system.forks[i]);
	pthread_mutex_destroy(&prog->system.status);
	pthread_mutex_destroy(&prog->system.write);
	free(prog->system.forks);
	free(prog->philo);
}