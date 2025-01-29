/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:10:28 by jgraf             #+#    #+#             */
/*   Updated: 2024/12/02 10:16:37 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	This is a simple atoi function that converts the input from a string to and integer
*	At the same time, the input is checked to make sure the input does not contain any
*	characters other than digits and are valid integers
*/

static int	is_valid(const char *str)
{
	int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i ++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	ft_atoi(const char	*str)
{
	long	val;
	int		i;

	val = 0;
	i = 0;
	if (!is_valid(str))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		val *= 10;
		val += str[i] - '0';
		i ++;
	}
	if (val > INT_MAX)
		return (-1);
	return (val);
}
