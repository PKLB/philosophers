/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-berr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:59:50 by ple-berr          #+#    #+#             */
/*   Updated: 2022/05/31 13:59:51 by ple-berr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_philosophers.h"

int	ft_check_number(char *nb[])
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (nb[i])
	{
		n = 0;
		while (nb[i][n])
		{
			if (nb[i][n] >= '0' && nb[i][n] <= '9')
				n++;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_check_number_size(char *nb[])
{
	int	i;

	i = 0;
	while (nb[i])
	{
		if (ft_atoi(nb[i]) > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

int	ft_checks(int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		if (ft_check_number(argv) != 0)
			return (ft_error("Please enter possible numbers only!\n"));
		if (ft_check_number_size(argv) != 0)
			return (ft_error("Please enter possible numbers only!\n"));
		return (0);
	}
	return (ft_error("Wrong number of arguments!\n"));
}
