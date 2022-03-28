#include "lib_philosophers.h"

int	ft_parsing(t_general *data, char *argv[], int argc)
{
	data->args.nb_of_philo = ft_atoi(argv[1]);
	data->args.time_die = ft_atoi(argv[2]);
	data->args.time_eat = ft_atoi(argv[3]);
	data->args.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->args.must_eat = ft_atoi(argv[5]);
	else
		data->args.must_eat = -1;
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 ||
		ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (ft_error("Wrong values entered!\n"));
	return (0);
}