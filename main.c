#include "lib_philosophers.h"

int	activity(t_philo *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	printf("MIAM IM EATING\n");
	return (0);
}

void*	test(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	if (data->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_create(&data[data->philo_id].thread_id, NULL, test, &data[data->philo_id]);
		activity(data);
		pthread_detach(data[data->philo_id].thread_id);
	}
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
	while (i < data.args.nb_of_philo)
	{
		pthread_create(&data.philo[i].thread_id, NULL, test, &data.philo[i]);
		printf("%ld | %d\n",(get_time() - data.args.start_time), data.philo[i].philo_id) ;
		i++;
	}
	return (0);
}