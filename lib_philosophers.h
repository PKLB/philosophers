// METTRE HEADER
#ifndef LIB_PHILOSOPHER_H
# define LIB_PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

//Structure with all the arguments that are gonna be the same for every philosopher
typedef struct	struct_arguments
{
	int	nb_of_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	must_eat;
}				t_arguments;

//Structure unique for each philosopher
typedef struct	struct_philo
{
	t_arguments *arguments;
	int			philo_id;
	int			test;
}				t_philo;

//General structure
typedef struct struct_general
{
	t_philo		*philo;
	t_arguments	args;
}				t_general;

void		ft_putstr(char *str);
long int	ft_atoi(const char *str);
int			ft_check_number(char **nb);

int			ft_error(char *str);
int 		ft_checks(int argc, char *argv[]);
int			ft_parsing(t_general *data, char *argv[], int argc);
int			start(t_general *data);

#endif
