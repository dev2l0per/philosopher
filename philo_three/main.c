/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:24:21 by juyang            #+#    #+#             */
/*   Updated: 2021/03/28 16:24:22 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int					ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int					check_arg(int argc, char **argv)
{
	int				i;
	int				j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (j < argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
			{
				printf("Error\n");
				return (-1);
			}
		}
	}
	if (ft_atoi(argv[1]) < 2)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (-1);
	}
	return (0);
}

int					prog_run(t_prog *prog)
{
	int				i;
	pthread_t		full_th;
	pthread_t		finish_ch;

	i = -1;
	prog->system.start_time = get_time();
	while (++i < prog->system.number_of_philosophers)
	{
		prog->philo[i].pid = fork();
		if (prog->philo[i].pid == -1)
			return (-1);
		else if (prog->philo[i].pid == 0)
		{
			solve((void *)&prog->philo[i]);
			exit(0);
		}
	}
	if (prog->system.number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_create(&full_th, NULL, full_check, (void *)prog);
		pthread_detach(full_th);
	}
	pthread_create(&finish_ch, NULL, finish_check, (void *)prog);
	pthread_join(finish_ch, NULL);
	return (0);
}

int					main(int argc, char **argv)
{
	t_prog			prog;

	if (!(argc == 5 || argc == 6))
		write(1, "Argument Error\n", 15);
	else
	{
		if (check_arg(argc, argv) == -1
		|| argument_init(&prog, argc, argv) == -1)
		{
			printf("Error\n");
			return (0);
		}
		if (semaphore_init(&prog) == -1)
		{
			printf("Error\n");
			return (0);
		}
		philosopher_init(&prog);
		if (prog_run(&prog) == -1)
			return (0);
		clear(&prog);
	}
	return (0);
}
