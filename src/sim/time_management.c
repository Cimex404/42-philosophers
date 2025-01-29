/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:42:09 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/16 16:35:52 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*	This function returns the time in milliseconds that have passed since the
*	start of the program.
*/

double	get_time(t_data data)
{
	int				s;
	long			us;
	struct timeval	t;

	gettimeofday(&t, NULL);
	pthread_mutex_lock(&data.time_mtx);
	us = (t.tv_usec - data.start_time_us);
	s = (t.tv_sec - data.start_time_s);
	pthread_mutex_unlock(&data.time_mtx);
	return ((s * 1000000 + us) / 1000);
}

/*	This is my own implementation of the usleep function.
*	usleep is (if you believe the rumors) very unrealiable and makes the program sleep
*	for "at least" the specified amount of time, but this one is much more precise.
*	But works only on a millisecond instead of a microsecond basis. 
*/

void	my_sleep(long time)
{
	struct timeval	s;
	struct timeval	c;
	long			elps;

	gettimeofday(&s, NULL);
	while (1)
	{
		gettimeofday(&c, NULL);
		elps = (c.tv_sec - s.tv_sec) * 1000000 + (c.tv_usec - s.tv_usec);
		if (elps >= time)
			break ;
		usleep(1000);
	}
}
