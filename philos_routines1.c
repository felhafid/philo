/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routines1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:28:26 by felhafid          #+#    #+#             */
/*   Updated: 2024/08/11 15:28:55 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_data *d, t_philo *p, char *s)
{
	pthread_mutex_lock(&d->mutex_dead);
	if (d->check_dead == 1)
	{
		pthread_mutex_lock(&d->msg);
		printf("%ld	%d %s", time_rn() - d->start, p->id, s);
		pthread_mutex_unlock(&d->msg);
	}
	pthread_mutex_unlock(&d->mutex_dead);
}

int	check_time_sleep(t_philo *p, long time)
{
	if ((int)(time_rn() - time) >= p->d->time_to_sleep)
	{
		if (p->d->nb_of_time_eating >= 1)
		{
			pthread_mutex_lock(&p->d->mutex_eat);
			if (p->d->times_eaten >= p->d->eat)
				return (pthread_mutex_unlock(&p->d->mutex_eat), -1);
			pthread_mutex_unlock(&p->d->mutex_eat);
		}
		usleep(200);
		if (eating(p) == -1)
			return (-1);
	}
	return (0);
}

int	check_sleep(t_philo *p)
{
	long	time;

	time = time_rn();
	while (1)
	{
		usleep(200);
		if (check_time_sleep(p, time) == -1)
			return (-1);
		if ((int)(time_rn() - p->last_meal) >= p->d->time_to_die)
		{
			pthread_mutex_lock(&p->d->mutex_dead);
			if (p->d->check_dead == 1)
			{
				p->d->check_dead = 0;
				pthread_mutex_lock(&p->d->msg);
				printf("%ld	%d died\n", time_rn() - p->d->start, p->id);
				pthread_mutex_unlock(&p->d->msg);
			}
			return (pthread_mutex_unlock(&p->d->mutex_dead), -1);
		}
	}
	return (0);
}

int	sleeping(t_philo *p)
{
	pthread_mutex_lock(&p->d->mutex_dead);
	if (p->d->check_dead == 0)
	{
		pthread_mutex_unlock(&p->d->mutex_dead);
		return (-1);
	}
	pthread_mutex_unlock(&p->d->mutex_dead);
	print_msg(p->d, p, "is sleeping\n");
	if (check_sleep(p) == -1)
		return (-1);
	return (0);
}
