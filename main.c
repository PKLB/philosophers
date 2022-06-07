/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-berr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:00:05 by ple-berr          #+#    #+#             */
/*   Updated: 2022/05/31 14:00:06 by ple-berr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_philosophers.h"

int	main(int argc, char *argv[])
{
	t_general	structure;

	if (ft_parsing(&structure, argv, argc) != 0 || start(&structure) != 0)
		return (1);
	pthread_mutex_init(&structure.args.end_threads, NULL);
	pthread_mutex_lock(&structure.args.end_threads);
	if (create_threads(&structure) != 0)
		return (1);
	ft_usleep(3);
	if (structure.args.finish_eat == 42)
		printf("Everyone ate enough !\n");
	else
		printf("%lld \e[1;33m%d\e[0;37m \e[1;91mdied\e[0;37m\n",
			get_time() - structure.args.start_time, 1);
	return (0);
}
