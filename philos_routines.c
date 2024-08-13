/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:28:13 by felhafid          #+#    #+#             */
/*   Updated: 2024/08/11 15:29:26 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_time_eat(t_philo *p, long time)
{
	pthread_mutex_lock(&p->d->mutex_dead);
	if (p->d->check_dead == 0)
	{
		pthread_mutex_unlock(&p->d->mutex_dead);
		pthread_mutex_unlock(p->left_fork);
		return (pthread_mutex_unlock(p->right_fork), -1);
	}
	pthread_mutex_unlock(&p->d->mutex_dead);
	if ((int)(time_rn() - time) >= p->d->time_to_eat)
	{
		p->last_meal = time_rn();
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		if (p->d->nb_of_time_eating >= 1)
		{
			pthread_mutex_lock(&p->d->mutex_eat);
			p->d->times_eaten += 1;
			if (p->d->times_eaten >= p->d->eat)
				return (pthread_mutex_unlock(&p->d->mutex_eat), -1);
			pthread_mutex_unlock(&p->d->mutex_eat);
		}
		if (sleeping(p) == -1)
			return (-1);
	}
	return (0);
}

int	check_lastmeal(t_philo *p)
{
	long	time;

	time = time_rn();
	while (1)
	{
		usleep(200);
		if (check_time_eat(p, time) == -1)
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
			pthread_mutex_unlock(&p->d->mutex_dead);
			pthread_mutex_unlock(p->left_fork);
			pthread_mutex_unlock(p->right_fork);
			return (-1);
		}
	}
	return (0);
}

int	take_fork(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&p->d->mutex_dead);
	if (p->d->check_dead == 0)
		return (pthread_mutex_unlock(p->left_fork),
			pthread_mutex_unlock(&p->d->mutex_dead), -1);
	pthread_mutex_unlock(&p->d->mutex_dead);
	print_msg(p->d, p, "has taken a fork\n");
	if (p->d->nb_philo == 1)
	{
		usleep(p->d->time_to_die * 1000);
		printf("%d	%d died\n", p->d->time_to_die, p->id);
		return (pthread_mutex_unlock(p->left_fork), -1);
	}
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->d->mutex_dead);
	if (p->d->check_dead == 0)
	{
		pthread_mutex_unlock(&p->d->mutex_dead);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		return (-1);
	}
	pthread_mutex_unlock(&p->d->mutex_dead);
	print_msg(p->d, p, "has taken a fork\n");
	return (0);
}

int	eating(t_philo *p)
{
	if (mutex(p->d) == -1)
		return (-1);
	print_msg(p->d, p, "is thinking\n");
	if (take_fork(p) == -1)
		return (-1);
	if (p->d->nb_of_time_eating >= 1)
	{
		pthread_mutex_lock(&p->d->mutex_eat);
		if (p->d->times_eaten >= p->d->eat)
		{
			pthread_mutex_unlock(&p->d->mutex_eat);
			pthread_mutex_unlock(p->left_fork);
			pthread_mutex_unlock(p->right_fork);
			return (-1);
		}
		pthread_mutex_unlock(&p->d->mutex_eat);
	}
	if (p->d->check_dead == 0)
		return (pthread_mutex_unlock(&p->d->mutex_dead),
			pthread_mutex_unlock(p->left_fork),
			pthread_mutex_unlock(p->right_fork), -1);
	print_msg(p->d, p, "is eating\n");
	if (check_lastmeal(p) == -1)
		return (-1);
	return (0);
}
