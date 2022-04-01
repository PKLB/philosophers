#include "lib_philosophers.h"

int	start(t_general *data)
{
	int	i;

	i = 0;
	while (i < data->args.nb_of_philo)
	{
		data->philo[i].philo_id = i;
		data->philo[i].nb_eat = 0;
		i++;
	}
	return (0);
}