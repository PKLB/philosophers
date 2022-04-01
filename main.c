#include "lib_philosophers.h"

int	activity(t_philo *arg, t_general *data)
{
	if (arg->philo_id % 2 == 0)
		ft_usleep(100);
	pthread_mutex_lock(&data->philo->mutex);
	printf("%ld %d is eating\n",(get_time() - data->args.start_time), arg->philo_id);
	data->args.finish_eat++;
	pthread_mutex_unlock(&data->philo->mutex);
	ft_usleep(data->args.time_eat);
	printf("%ld %d is sleeping\n",(get_time() - data->args.start_time), arg->philo_id);
	ft_usleep(data->args.time_sleep);
	return (0);
}

void* mama(void *arg)
{
	(void) arg;
	pthread_exit(EXIT_SUCCESS);
}

void*	test(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;

	/*while (1)
	{
		pthread_create(&data[data->philo_id].thread_id, NULL, mama, &data[data->philo_id]);
		pthread_detach(data[data->philo_id].thread_id);
	}*/
	pthread_exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	int	i;

	i = 0;
	t_general	data;
	if (ft_checks(argc, &argv[1]) != 0)
		return (1);
	if (ft_parsing(&data, argv, argc) != 0)
		return (1);
	data.philo = malloc(sizeof(t_philo) * data.args.nb_of_philo);
	if (data.philo == NULL)
		return (1);
	if (start(&data) != 0)
		return (1);
	pthread_mutex_init(&data.philo->mutex, NULL);
	while (i < data.args.nb_of_philo)
	{
		pthread_create(&data.philo[i].thread_id, NULL, test, &data.philo[i]);
		pthread_detach(data.philo[i].thread_id);
		i++;
	}
	i = 0;
	while (data.args.finish_eat != data.args.must_eat)
	{
		if (i == data.args.nb_of_philo)
			i = 0;
		activity(&data.philo[i], &data);
		i++;
	}
	return (0);
}
