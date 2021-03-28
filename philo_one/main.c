/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:18:54 by juyang            #+#    #+#             */
/*   Updated: 2021/03/23 16:18:55 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int					check_arg(int argc, char **argv)
{
	int				i;
	int				j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (j < argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error\n");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void				prog_run(t_prog *prog)
{
	int				i;
	pthread_t		full_th;

	i = 0;
	prog->system.finish = 0;
	prog->system.start_time = get_time();
	while (i < prog->system.number_of_philosophers)
	{
		pthread_create(&prog->philo[i].p_thread, NULL, solve, (void *)&prog->philo[i]);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < prog->system.number_of_philosophers)
		pthread_join(prog->philo[i++].p_thread, NULL);
	if (prog->system.number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_create(&full_th, NULL, full_check, (void *)prog);
		pthread_detach(full_th);
	}
}


int					main(int argc, char **argv)
{
	t_prog			prog;

	if (!(argc == 5 || argc == 6))
		write(1, "Argument Error\n", 15);
	else
	{
		if (check_arg(argc, argv) == -1)
			return (0);
		if (argument_init(&prog, argc, argv) == -1)
			return (0);
		if (prog.system.number_of_philosophers < 2)
		{
			printf("Error\n");
			return (0);
		}
		philosopher_init(&prog);
		mutex_init(&prog);
		prog_run(&prog);
		clear(&prog);
	}
	return (0);
}
