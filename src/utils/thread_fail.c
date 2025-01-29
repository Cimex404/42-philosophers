/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_fail.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:29:00 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/06 12:29:03 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_failure(t_data *data, char *msg)
{
	pthread_mutex_destroy(&data->eat_mtx);
	pthread_mutex_destroy(&data->sim_over_mtx);
	pthread_mutex_destroy(&data->time_mtx);
	pthread_mutex_destroy(&data->philo_mtx);
	free_forks(data, data->phil_nmb);
	error_and_free(msg, data);
}
