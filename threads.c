/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:30:16 by felhafid          #+#    #+#             */
/*   Updated: 2024/08/12 10:49:46 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_handler(void *b)
{
	t_philo	*p;

	p = (t_philo *)b;
	if (p->state == 1)
	{
		if (eating(p) == -1)
			return (NULL);
	}
	else
	{
		if (sleeping(p) == -1)
			return (NULL);
	}
	return (NULL);
}

long	time_rn(void)
{
	struct timeval	time_rn;
	long			time;

	if (gettimeofday(&time_rn, NULL) != 0)
		return (-1);
	time = time_rn.tv_sec * 1000 + time_rn.tv_usec / 1000;
	return (time);
}

void	init_mutex(t_data *p)
{
	int	i;

	i = 0;
	pthread_mutex_init(&p->mutex_dead, NULL);
	pthread_mutex_init(&p->mutex_eat, NULL);
	pthread_mutex_init(&p->msg, NULL);
	if (p->nb_of_time_eating >= 1)
	{
		p->times_eaten = 0;
		p->eat = p->nb_of_time_eating * p->nb_philo;
	}
	p->start = time_rn();
	while (i < p->nb_philo)
	{
		pthread_mutex_init(p->forks[i], NULL);
		p->philos[i].last_meal = p->start;
		p->philos[i].d = p;
		i++;
	}
	return ;
}

int	create_threads(t_data *p)
{
	pthread_t	*tid;
	int			i;

	i = 0;
	tid = malloc(sizeof(pthread_t) * p->nb_philo);
	if (!tid)
		return (-1);
	init_mutex(p);
	i = 0;
	while (i < p->nb_philo)
	{
		if (pthread_create(&tid[i], NULL, thread_handler, &p->philos[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < p->nb_philo)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	free(tid);
	return (0);
}
