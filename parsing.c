#include "lib_philosophers.h"

int	ft_parsing(t_general *data, char *argv[], int argc)
{
	if (ft_checks(argc, &argv[1]) != 0)
		return (1);
	data->args.nb_of_philo = ft_atoi(argv[1]);
	data->args.time_die = ft_atoi(argv[2]);
	data->args.time_eat = ft_atoi(argv[3]);
	data->args.time_sleep = ft_atoi(argv[4]);
	data->args.start_time = get_time();
	data->args.finish_eat = -1;
	if (argc == 6)
		data->args.must_eat = ft_atoi(argv[5]);
	else
		data->args.must_eat = -1;
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (ft_error("Wrong values entered!\n"));
	return (0);
}

int	start(t_general *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->args.nb_of_philo + 1);
	while (++i < data->args.nb_of_philo)
	{
		data->philo[i].args = &data->args;
		data->philo[i].nb_eat = 0;
		data->philo[i].finished_eating = -1;
		data->philo[i].philo_id = i + 1;
	}
	return (0);
}
