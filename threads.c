/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-berr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:00:19 by ple-berr          #+#    #+#             */
/*   Updated: 2022/05/31 14:00:20 by ple-berr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_philosophers.h"

void	sleep_routine(t_philo *structure)
{
	print_action(structure, 1);
	ft_usleep(2);
}

void	living_the_life(t_philo *structure)
{
	pthread_mutex_lock(&structure->left_fork);
	print_action(structure, 3);
	pthread_mutex_lock(structure->right_fork);
	print_action(structure, 3);
	print_action(structure, 2);
	pthread_mutex_lock(&structure->get_meal);
	structure->last_meal = get_time();
	pthread_mutex_unlock(&structure->get_meal);
	ft_usleep(structure->args->time_eat);
	pthread_mutex_unlock(&structure->left_fork);
	pthread_mutex_unlock(structure->right_fork);
	print_action(structure, 1);
	ft_usleep(structure->args->time_sleep);
	print_action(structure, 0);
}

void	*check_death(void	*params)
{
	t_philo		*s;
	long long	time;
	long long	last_meal;

	s = (t_philo *)params;
	while (1)
	{
		pthread_mutex_lock(&s->args->get_time);
		time = get_time() - s->args->start_time;
		pthread_mutex_unlock(&s->args->get_time);
		pthread_mutex_lock(&s->args->check_death);
		last_meal = ((s->last_meal - s->args->start_time) + s->args->time_die);
		if (last_meal < time)
		{
			if (last_meal < time)
			{
				pthread_mutex_unlock(&s->args->end_threads);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&s->args->check_death);
	}
	return (NULL);
}

void	*routine(void *params)
{
	t_philo		*structure;

	structure = (t_philo *)params;
	if (structure->philo_id % 2 == 0)
		sleep_routine(params);
	while (1)
	{
		living_the_life(structure);
		if (++structure->nb_eat == structure->args->must_eat)
		{
			pthread_mutex_lock(&structure->args->check_eat);
			structure->args->finish_eat++;
			if (structure->args->finish_eat == structure->args->nb_of_philo - 1)
			{
				pthread_mutex_unlock(&structure->args->end_threads);
				structure->args->finish_eat = 42;
				pthread_mutex_unlock(&structure->args->check_eat);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&structure->args->check_eat);
	}
	return (NULL);
}

int	create_threads(t_general *stru)
{
	int	i;

	i = -1;
	pthread_mutex_init(&stru->args.check_death, NULL);
	pthread_mutex_init(&stru->args.get_time, NULL);
	pthread_mutex_init(&stru->args.check_eat, NULL);
	while (i++ < stru->args.nb_of_philo - 1)
	{
		pthread_mutex_lock(&stru->args.check_death);
		if (pthread_create(&stru->philo[i].thread_id, NULL,
				routine, &stru->philo[i]) == -1)
			return (1);
		pthread_mutex_unlock(&stru->args.check_death);
		pthread_mutex_lock(&stru->args.check_death);
		if (pthread_create(&stru->philo[i].thread_id, NULL,
				check_death, &stru->philo[i]) == -1)
			return (1);
		pthread_mutex_unlock(&stru->args.check_death);
		if (i + 1 == stru->args.nb_of_philo && stru->args.finish_eat == -1)
			pthread_mutex_lock(&stru->args.end_threads);
	}
	return (0);
}
