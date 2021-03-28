/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:14:18 by juyang            #+#    #+#             */
/*   Updated: 2021/03/23 16:14:19 by juyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

# define	ALIVE 0
# define	FULL 1
# define	DIED 2

typedef struct		s_system
{
	int				number_of_philosophers;
	int				finish;
	int				number_of_times_each_philosopher_must_eat;
	long long int	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	status;
	pthread_mutex_t write;
	pthread_mutex_t finish_check;
}					t_system;

typedef struct		s_philosopher
{
	pthread_t		p_thread;
	int				index;
	int				eat_cnt;
	long long int	last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_prog	*prog_ptr;
	int				status;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
}					t_philosopher;

typedef struct		s_prog
{
	t_philosopher	*philo;
	t_system		system;
}					t_prog;

void				prog_run(t_prog *prog);

int					argument_init(t_prog *prog, int argc, char **argv);
void				philosopher_init(t_prog *prog);
void				mutex_init(t_prog *prog);

long long int		get_time(void);
int					ft_atoi(const char *str);
void				print_state(char *str, t_philosopher *philo);
int					ft_isdigit(int c);
void				clear(t_prog *prog);

void				*solve(void *arg);
void				sleeping(t_philosopher *philo);
void				take_fork(t_philosopher *philo);
void				eating(t_philosopher *philo);

void				*death_check(void *arg);
void				*full_check(void *arg);

#endif