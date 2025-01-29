/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:18:51 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/05 08:59:01 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	error_and_free(const char *msg, t_data *data)
{
	if (data->philos != NULL)
		free(data->philos);
	if (data->forks != NULL)
		free(data->forks);
	error(msg);
}

void	free_forks(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i ++;
	}
}

void	join_threads(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i ++;
	}
}

void	cleanup(t_data *data)
{
	free_forks(data, data->phil_nmb);
	free(data->philos);
	free(data->forks);
}
