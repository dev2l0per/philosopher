/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:36:35 by juyang            #+#    #+#             */
/*   Updated: 2021/03/29 16:36:36 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void				ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void				ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
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
