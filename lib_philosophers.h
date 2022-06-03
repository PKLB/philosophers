/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_philosophers.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-berr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:00:00 by ple-berr          #+#    #+#             */
/*   Updated: 2022/05/31 14:00:00 by ple-berr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PHILOSOPHERS_H
# define LIB_PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

//Structure with all the arguments that are gonna be the same
//for every philosopher
typedef struct struct_arguments
{
	int				nb_of_philo;
	long long		time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				finish_eat;
	long long		start_time;
	pthread_mutex_t	get_time;
	pthread_mutex_t	check_eat;
	pthread_mutex_t	check_death;
	pthread_mutex_t	end_threads;
}				t_arguments;

//Structure unique for each philosopher
typedef struct struct_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	get_meal;
	t_arguments		*args;
	long long		last_meal;
	int				nb_eat;
	int				finished_eating;
	int				philo_id;
}					t_philo;

//General structure
typedef struct struct_general
{
	t_philo		*philo;
	t_arguments	args;
}				t_general;

void		ft_putstr(char *str);
long long	ft_atoi(const char *str);
int			ft_check_number(char **nb);
long long	get_time(void);
void		ft_usleep(long long time_in_ms);
int			ft_error(char *str);
int			ft_checks(int argc, char *argv[]);
int			ft_parsing(t_general *data, char *argv[], int argc);
int			start(t_general *data);
void		print_args(t_general data, int show_philo);
int			create_threads(t_general *structure);
void		print_action(t_philo *structure, int i);
void		print_args(t_general data, int show_philo);

#endif
