/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:28:41 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/16 16:35:01 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	These functions are creating and setting up a thread for each philosopher and one monitor
*	It also initialized mutexes that make sure no two philosophers can alter the data at the same time.
*	After the threads are created, the even numbered philosophers do nothing while the others already
*	start eating. This way, the philosophers are alway switching between eating and sleeping in two groups.
*/

static void	*sync_threads(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = philo->data;
	print_msg(INIT, data, *philo);
	if (philo->philo_id % 2)
		my_sleep(data->eat_time * 1000);
	simulation(philo, data);
	return (NULL);
}

static void	after_sim_cleanup(t_data *data, int i)
{
	join_threads(data, i);
	pthread_mutex_destroy(&data->eat_mtx);
	pthread_mutex_destroy(&data->sim_over_mtx);
	pthread_mutex_destroy(&data->time_mtx);
	pthread_mutex_destroy(&data->philo_mtx);
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->eat_mtx, NULL);
	pthread_mutex_init(&data->sim_over_mtx, NULL);
	pthread_mutex_init(&data->time_mtx, NULL);
	pthread_mutex_init(&data->philo_mtx, NULL);
	while (i < data->phil_nmb)
	{
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].thread_id, NULL,
				sync_threads, (void *)&data->philos[i]))
			thread_failure(data, "Thread creation failure!");
		i ++;
	}
	mon_sim(data);
	after_sim_cleanup(data, i);
}
