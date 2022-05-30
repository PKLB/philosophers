#include "lib_philosophers.h"

void	print_args(t_general data, int show_philo)
{
	int	i;

	i = 0;
	printf("\e[4;36m#***********************************************#\e[0;37m\n");
	printf("%-10s\e[1;33m%d\e[0;37m\n", "\e[4;36m#\e[0;37m Number of philo: ", data.args.nb_of_philo);
	printf("\e[4;36m#\e[0;37m Time to die: \e[1;33m%d\e[0;37m 💀\n", data.args.time_die);
	printf("\e[4;36m#\e[0;37m Time to eat: \e[1;33m%d\e[0;37m 🍜\n", data.args.time_eat);
	printf("\e[4;36m#\e[0;37m Time to sleep: \e[1;33m%d\e[0;37m 🛌\n", data.args.time_sleep);
	printf("\e[4;36m#\e[0;37m Finished to eat: \e[1;33m%d\e[0;37m \n", data.args.finish_eat);
	if (data.args.must_eat > 0)
		printf("\e[4;36m#\e[0;37m Has to eat: \e[1;33m%d\e[0;37m times\n", data.args.must_eat);
	printf("\e[4;36m#***********************************************#\e[0;37m\n");
	if (show_philo == 1)
	{
		printf("\e[4;32m#***********************************************#\e[0;37m\n");;
		while (i < data.args.nb_of_philo)
		{
			printf("\e[4;32m#\e[0;37m Philo nb \e[1;33m%d\e[0;37m has eaten \e[1;33m%d\e[0;37m times 🍜\n", data.philo[i].philo_id, data.philo[i].nb_eat);
			if (data.philo[i].finished_eating == -1)
				printf("\e[4;32m#\e[0;37m Philo nb \e[1;33m%d\e[0;37m has not finished to eat 🍗\n", data.philo[i].philo_id);
			else
				printf("\e[4;32m#\e[0;37m Philo nb \e[1;33m%d\e[0;37m has finished to eat 🍗\n", data.philo[i].philo_id);
			i++;
		}
		printf("\e[4;32m#***********************************************#\e[0;37m\n");;
	}
}

void	print_action(t_philo *structure, int i)
{
	if (i == 0)
		printf("%ld \e[1;33m%d\e[0;37m is \e[0;36mthinking\e[0;37m\n",(get_time() - structure->args->start_time), structure->philo_id);
	if (i == 1)
		printf("%ld \e[1;33m%d\e[0;37m is \e[0;35msleeping\e[0;37m\n",(get_time() - structure->args->start_time), structure->philo_id);
	if (i == 2)
		printf("%ld \e[1;33m%d\e[0;37m is \e[0;32meating\e[0;37m\n",(get_time() - structure->args->start_time), structure->philo_id);
}

void	sleep_routine(t_philo *structure)
{
	print_action(structure, 1);
}

void	living_the_life(t_philo *structure)
{
	pthread_mutex_lock(&structure->left_fork);
	print_action(structure, 2);
	ft_usleep(structure->args->time_eat);
	print_action(structure, 1);
	pthread_mutex_unlock(&structure->left_fork);
	ft_usleep(structure->args->time_sleep);
	print_action(structure, 0);

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
			printf("Philo \e[1;33m%d\e[0;37m ate enough !\n", structure->philo_id);
			return (NULL);
		}
	}
	return (NULL);
}

int	create_threads(t_general *structure)
{
	int	i;

	i = -1;
	while (i++ < structure->args.nb_of_philo - 1)
	{
		if (pthread_create(&structure->philo[i].thread_id, NULL,
				routine, &structure->philo[i]) == -1)
			return (1);
		pthread_mutex_init(&structure->philo[i].left_fork, NULL);
	}
	i = -1;
	while (i++ < structure->args.nb_of_philo - 1)
	{
		if (pthread_join(structure->philo[i].thread_id, NULL) != 0)
			return (1);
		pthread_mutex_destroy(&structure->philo[i].left_fork);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_general	structure;

	if (ft_parsing(&structure, argv, argc) != 0 || start(&structure) != 0)
		return (1);
	print_args(structure, 0);
	if (create_threads(&structure) != 0)
		return (1);
	return (0);
}
