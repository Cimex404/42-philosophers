/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:31:59 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/13 12:17:05 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	This one is pretty simple.
*	Wait for your first fork, wait for your second fork.
*	Eat as soon as you have both forks, after eating, put the forks down and sleep
*	After sleeping, think while waiting for the first fork.
*/

static void	fork_routine(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_msg(FORK, data, *philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_msg(FORK, data, *philo);
	print_msg(EAT, data, *philo);
}

static void	sleep_think_routine(t_philo *philo, t_data *data)
{
	my_sleep(data->eat_time * 1000);
	print_msg(SLEEP, data, *philo);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
	my_sleep(data->slp_time * 1000);
	print_msg(THINK, data, *philo);
	my_sleep(data->die_time - (get_time(*data) - philo->last_meal));
}

void	simulation(t_philo *philo, t_data *data)
{
	while (1)
	{
		fork_routine(philo, data);
		pthread_mutex_lock(&data->philo_mtx);
		philo->meals ++;
		philo->last_meal = get_time(*data);
		pthread_mutex_unlock(&data->philo_mtx);
		sleep_think_routine(philo, data);
		pthread_mutex_lock(&data->sim_over_mtx);
		if (data->sim_is_over)
		{
			pthread_mutex_unlock(&data->sim_over_mtx);
			break ;
		}
		pthread_mutex_unlock(&data->sim_over_mtx);
	}
}
