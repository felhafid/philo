/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:19:20 by felhafid          #+#    #+#             */
/*   Updated: 2024/08/09 17:01:24 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args(char **s, t_data *p, int ac)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (ft_atoi(s[i]) == -1)
			return (-1);
		i++;
	}
	p->nb_philo = ft_atoi(s[1]);
	p->time_to_die = ft_atoi(s[2]);
	p->time_to_eat = ft_atoi(s[3]);
	p->time_to_sleep = ft_atoi(s[4]);
	if (ac == 6)
		p->nb_of_time_eating = ft_atoi(s[5]);
	else
		p->nb_of_time_eating = -1;
	return (0);
}

void	assign_philos(t_data *p)
{
	int	i;

	i = 0;
	p->check_dead = 1;
	while (i < p->nb_philo)
	{
		p->philos[i].id = i + 1;
		if (i % 2 == 0)
			p->philos[i].state = 1;
		else
			p->philos[i].state = 0;
		if (i == 0)
			p->philos[i].right_fork = p->forks[p->nb_philo - 1];
		else
			p->philos[i].right_fork = p->forks[i - 1];
		p->philos[i].left_fork = p->forks[i];
		i++;
	}
}

int	setup_philos(t_data *p)
{
	int	i;

	p->philos = malloc(sizeof(t_philo) * p->nb_philo);
	if (!p->philos)
		return (-1);
	p->forks = malloc(sizeof(pthread_mutex_t *) * p->nb_philo);
	if (!p->forks)
		return (-1);
	i = 0;
	while (i < p->nb_philo)
	{
		p->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!p->forks[i])
			return (-1);
		i++;
	}
	assign_philos(p);
	return (0);
}
