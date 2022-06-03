/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-berr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:00:15 by ple-berr          #+#    #+#             */
/*   Updated: 2022/05/31 14:00:17 by ple-berr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_philosophers.h"

void	print_args(t_general data, int show_philo)
{
	int	i;

	i = 0;
	printf("\e[4;36m#*******************************************#\e[0;37m\n");
	printf("%-10s\e[1;33m%d\e[0;37m\n", "\e[4;36m#\e[0;37m Number of philo: ",
		data.args.nb_of_philo);
	printf("\e[4;36m#\e[0;37m Time to die: \e[1;33m%lld\e[0;37m 💀\n",
		data.args.time_die);
	printf("\e[4;36m#\e[0;37m Time to eat: \e[1;33m%d\e[0;37m 🍜\n",
		data.args.time_eat);
	printf("\e[4;36m#\e[0;37m Time to sleep: \e[1;33m%d\e[0;37m 🛌\n",
		data.args.time_sleep);
	printf("\e[4;36m#\e[0;37m Finished to eat: \e[1;33m%d\e[0;37m \n",
		data.args.finish_eat);
	if (data.args.must_eat > 0)
		printf("\e[4;36m#\e[0;37m Has to eat: \e[1;33m%d\e[0;37m times\n",
			data.args.must_eat);
	printf("\e[4;36m#*******************************************#\e[0;37m\n");
	if (show_philo == 1)
	{
		printf("\e[4;32m#**************************************#\e[0;37m\n");
		while (i < data.args.nb_of_philo)
		{
			printf("\e[4;32m#\e[0;37m Philo nb \e[1;33m%d\e[0;37m has eaten \e[1;33m%d\e[0;37m times 🍜\n", data.philo[i].philo_id, data.philo[i].nb_eat);
			if (data.philo[i].finished_eating == -1)
				printf("\e[4;32m#\e[0;37m Philo nb \e[1;33m%d\e[0;37m has not finished to eat 🍗\n", data.philo[i].philo_id);
			else
				printf("\e[4;32m#\e[0;37m Philo nb \e[1;33m%d\e[0;37m has finished to eat 🍗\n", data.philo[i].philo_id);
			i++;
		}
		printf("\e[4;32m#************************************#\e[0;37m\n");
	}
}

void	print_action(t_philo *structure, int i)
{
	if (i == 0)
		printf("%lld \e[1;33m%d\e[0;37m is \e[0;36mthinking\e[0;37m\n",
			(get_time() - structure->args->start_time), structure->philo_id);
	if (i == 1)
		printf("%lld \e[1;33m%d\e[0;37m is \e[0;35msleeping\e[0;37m\n",
			(get_time() - structure->args->start_time), structure->philo_id);
	if (i == 2)
		printf("%lld \e[1;33m%d\e[0;37m is \e[0;32meating\e[0;37m\n",
			(get_time() - structure->args->start_time), structure->philo_id);
	if (i == 3)
		printf("%lld \e[1;33m%d\e[0;37m has taken a fork\n",
			(get_time() - structure->args->start_time), structure->philo_id);
}
