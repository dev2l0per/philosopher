/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:30:09 by juyang            #+#    #+#             */
/*   Updated: 2021/03/28 14:30:10 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	return ((int)(sign * res));
}

void				print_state(char *str, t_philosopher *philo)
{
	if (philo->status != DIED && philo->status != FULL
	&& philo->prog_ptr->system.finish == 0)
	{
		sem_wait(philo->prog_ptr->system.write);
		printf("%lldms %d ", get_time() -
		philo->prog_ptr->system.start_time, philo->index);
		printf("%s\n", str);
		sem_post(philo->prog_ptr->system.write);
	}
	else if (philo->status == DIED)
	{
		sem_wait(philo->prog_ptr->system.write);
		printf("%lldms %d ", get_time() -
		philo->prog_ptr->system.start_time, philo->index);
		printf("%s\n", str);
		sem_post(philo->prog_ptr->system.write);
	}
}

void				clear(t_prog *prog)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/status");
	sem_unlink("/finish_check");
	sem_close(prog->system.forks);
	sem_close(prog->system.write);
	sem_close(prog->system.status);
	sem_close(prog->system.finish_check);
	free(prog->philo);
}
