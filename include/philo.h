/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 08:20:42 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/06 11:51:01 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

/*	MACROS	*/
# define INIT 0
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5
# define FULL 6

/*	Structs	*/

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
	int				used_by;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread_id;
	int			philo_id;
	int			meals;
	int			last_meal;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_data		*data;
}	t_philo;

struct s_data
{
	int				phil_nmb;
	int				die_time;
	int				slp_time;
	int				eat_time;
	int				meal_nmb;
	int				ready_count;
	int				sim_is_over;
	long			start_time_s;
	long			start_time_us;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	eat_mtx;
	pthread_mutex_t	sim_over_mtx;
	pthread_mutex_t	time_mtx;
	pthread_mutex_t	philo_mtx;
};

/*	Functions	*/
/*	Input and parsing	*/
void	init_data(t_data *data, int ac, char **av);
int		ft_atoi(const char	*str);

/*	Error and Malloc handle	*/
void	error(const char *msg);
void	error_and_free(const char *msg, t_data *data);
void	free_forks(t_data *data, int n);
void	join_threads(t_data *data, int n);
void	thread_failure(t_data *data, char *msg);
void	cleanup(t_data *data);

/*	Time and Messages	*/
double	get_time(t_data data);
void	my_sleep(long time);
void	print_msg(int type, t_data *d, t_philo p);

/*	Simulation	*/
void	start_simulation(t_data *data);
void	simulation(t_philo *philo, t_data *data);
void	*mon_sim(t_data *data);

#endif
