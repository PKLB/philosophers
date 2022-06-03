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
	ft_usleep(1);
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
	pthread_mutex_unlock(structure->right_fork);
	pthread_mutex_unlock(&structure->left_fork);
	print_action(structure, 1);
	ft_usleep(structure->args->time_sleep);
	print_action(structure, 0);
}

void	*check_death(void	*params)
{
	t_philo		*structure;
	long long	time;
	long long	last_meal;

	structure = (t_philo *)params;
	while (1)
	{
		pthread_mutex_lock(&structure->args->get_time); 
		time = get_time() - structure->args->start_time;
		last_meal = ((structure->last_meal - structure->args->start_time) + structure->args->time_die);
		if (last_meal < time)
		{
			pthread_mutex_unlock(&structure->args->get_time); 
			pthread_mutex_unlock(&structure->args->end_threads);
			return (NULL);
		}
		pthread_mutex_unlock(&structure->args->get_time); 
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

int	create_threads(t_general *structure)
{
	int	i;

	i = -1;
	pthread_mutex_init(&structure->args.check_death, NULL);
	pthread_mutex_init(&structure->args.get_time, NULL);
	pthread_mutex_init(&structure->args.check_eat, NULL);
	while (i++ < structure->args.nb_of_philo - 1)
	{
		if (pthread_create(&structure->philo[i].thread_id, NULL,
				routine, &structure->philo[i]) == -1)
			return (1);
		pthread_mutex_lock(&structure->args.check_death);
		if (pthread_create(&structure->philo[i].thread_id, NULL,
				check_death, &structure->philo[i]) == -1)
			return (1);
		pthread_mutex_unlock(&structure->args.check_death);
		if (i + 1 == structure->args.nb_of_philo && structure->args.finish_eat == -1)
			pthread_mutex_lock(&structure->args.end_threads);
	}
	return (0);
}
