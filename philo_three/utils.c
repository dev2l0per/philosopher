/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:24:53 by juyang            #+#    #+#             */
/*   Updated: 2021/03/28 16:24:55 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		ft_putnbr_fd(get_time() - philo->prog_ptr->system.start_time, 1);
		ft_putstr_fd("ms ", 1);
		ft_putnbr_fd(philo->index, 1);
		ft_putstr_fd(str, 1);
		ft_putchar_fd('\n', 1);
		sem_post(philo->prog_ptr->system.write);
	}
	else if (philo->status == DIED)
	{
		sem_wait(philo->prog_ptr->system.write);
		ft_putnbr_fd(get_time() - philo->prog_ptr->system.start_time, 1);
		ft_putstr_fd("ms ", 1);
		ft_putnbr_fd(philo->index, 1);
		ft_putstr_fd(str, 1);
		ft_putchar_fd('\n', 1);
		sem_post(philo->prog_ptr->system.write);
	}
}

void				clear(t_prog *prog)
{
	int				i;

	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("status");
	sem_unlink("finish_check");
	sem_close(prog->system.forks);
	sem_close(prog->system.write);
	sem_close(prog->system.status);
	sem_close(prog->system.finish_check);
	i = -1;
	while (++i < prog->system.number_of_philosophers)
		kill(prog->philo[i].pid, SIGKILL);
	free(prog->philo);
}

void				ft_putnbr_fd(long long int n, int fd)
{
	char		c;
	long long	nbr;

	if (fd < 0)
		return ;
	nbr = n;
	if (nbr == 0)
	{
		write(fd, "0", 1);
	}
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = nbr * -1;
	}
	if (nbr > 0)
	{
		if (nbr / 10 > 0)
			ft_putnbr_fd(nbr / 10, fd);
		c = nbr % 10 + '0';
		write(fd, &c, 1);
	}
}
