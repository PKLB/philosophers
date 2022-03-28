#include "lib_philosophers.h"

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
		printf("Philo %d | %d\n",data.philo[i].philo_id, data.philo[i].test);
		i++;
	}
	return (0);
}