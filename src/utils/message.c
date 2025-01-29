/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:31:30 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/16 16:52:13 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(int type, t_data *d, t_philo p)
{
	pthread_mutex_lock(&d->sim_over_mtx);
	if (!d->sim_is_over)
	{
		pthread_mutex_lock(&d->philo_mtx);
		if (type != FULL)
			printf("%.0f\t[%i]\t", get_time(*d), p.philo_id);
		pthread_mutex_unlock(&d->philo_mtx);
		if (type == INIT)
			printf(" has taken a seat.\n");
		else if (type == FORK)
			printf(" has taken a fork.\n");
		else if (type == EAT)
			printf(" is eating.\n");
		else if (type == SLEEP)
			printf(" is sleeping.\n");
		else if (type == THINK)
			printf(" is thinking.\n");
		else if (type == DIE)
			printf(" has died.\n");
		else if (type == FULL)
			printf("\n🥳 Everyone has eaten %i meals. 🥳\n", d->meal_nmb);
		else
			printf("started doing cartwheels.\n");
	}
	pthread_mutex_unlock(&d->sim_over_mtx);
}
