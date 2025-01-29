/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:13:05 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/16 16:51:44 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*	These functions set up the data for the simulation.
*	First, all the input arguments are converted to integers and set as values in the data struct. 
*	Then, all philosophers are created and assigned two forks, namely the one to their left and right.
*	It is important to note that even numbered philosophers get asigned their right fork as their first fork
*	and odd numbered, the fork on their left. This is to prevent a death loop, where all philosophers take their
*	right fork first and wait for the philosopher on their left to release their fork. This would mean infinite waiting
*	because philosophers only put down the fork, after eating.
*/

static void	check_value_out_of_bounds(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1)
			error("Invalid input!");
		i ++;
	}
	if ((ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		|| ft_atoi(av[2]) < 60
		|| ft_atoi(av[3]) < 60
		|| ft_atoi(av[4]) < 60
		|| (ac == 6 && ft_atoi(av[5]) == 0))
		error("One or more inputs are out of bounds!");
}

static void	assign_forks(t_data *data, int i)
{
	if (data->philos[i].philo_id % 2 == 0)
	{
		data->philos[i].first_fork = &data->forks[i];
		data->philos[i].second_fork = &data->forks[data->phil_nmb - 1];
		if (i > 0)
			data->philos[i].second_fork = &data->forks[i - 1];
	}
	else
	{
		data->philos[i].second_fork = &data->forks[i];
		data->philos[i].first_fork = &data->forks[data->phil_nmb - 1];
		if (i > 0)
			data->philos[i].first_fork = &data->forks[i - 1];
	}
}

static void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phil_nmb)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = 0;
		assign_forks(data, i);
		i ++;
	}
}

static void	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->phil_nmb);
	data->philos = malloc(sizeof(t_philo) * data->phil_nmb);
	if (data->forks == NULL || data->philos == NULL)
		error_and_free("Malloc Failure!", data);
	while (i < data->phil_nmb)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
		{
			free_forks(data, i);
			error_and_free("Mutex_init Failure!", data);
		}
		data->forks[i].fork_id = i;
		data->forks[i].used_by = -1;
		i ++;
	}
	init_philo(data);
}

void	init_data(t_data *data, int ac, char **av)
{
	struct timeval	start;

	check_value_out_of_bounds(ac, av);
	data->phil_nmb = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->slp_time = ft_atoi(av[4]);
	data->meal_nmb = -1;
	if (ac == 6)
		data->meal_nmb = ft_atoi(av[5]);
	gettimeofday(&start, NULL);
	data->start_time_s = start.tv_sec;
	data->start_time_us = start.tv_usec;
	data->sim_is_over = 0;
	data->ready_count = 0;
	init_fork(data);
}
