/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:51:12 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/13 12:14:02 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	The monitor thread cycles through each philosopher and checks how far away they are from death
*	every few milliseconds.
*	Additionally, if all philosophers have eaten enough, the simulation is set to complete and the thread
*	exists the loop.
*/

static int	min_meals(t_data *data)
{
	int	i;
	int	m;

	i = 0;
	m = -1;
	pthread_mutex_lock(&data->philo_mtx);
	while (i < data->phil_nmb)
	{
		if (data->philos[i].meals < m || m == -1)
			m = data->philos[i].meals;
		i ++;
	}
	pthread_mutex_unlock(&data->philo_mtx);
	return (m);
}

static void	case_death(t_data *d, int i)
{
	pthread_mutex_lock(&d->philo_mtx);
	if ((get_time(*d) - d->philos[i].last_meal) <= d->die_time)
	{
		pthread_mutex_unlock(&d->philo_mtx);
		return ;
	}
	pthread_mutex_unlock(&d->philo_mtx);
	if (d->phil_nmb == 1)
		pthread_mutex_unlock(&d->philos[0].first_fork->fork);
	print_msg(DIE, d, d->philos[i]);
	pthread_mutex_lock(&d->sim_over_mtx);
	d->sim_is_over = 1;
	pthread_mutex_unlock(&d->sim_over_mtx);
}

static void	case_full(t_data *d, int i)
{
	if (min_meals(d) < d->meal_nmb || d->meal_nmb < 0)
		return ;
	print_msg(FULL, d, d->philos[i]);
	pthread_mutex_lock(&d->sim_over_mtx);
	d->sim_is_over = 1;
	pthread_mutex_unlock(&d->sim_over_mtx);
}

static void	check_death_or_full(t_data *d)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < d->phil_nmb)
		{
			case_death(d, i);
			case_full(d, i);
			i ++;
			pthread_mutex_lock(&d->sim_over_mtx);
			if (d->sim_is_over)
			{
				pthread_mutex_unlock(&d->sim_over_mtx);
				return ;
			}
			pthread_mutex_unlock(&d->sim_over_mtx);
		}
		my_sleep(500);
	}
}

void	*mon_sim(t_data *data)
{
	check_death_or_full(data);
	return (NULL);
}
