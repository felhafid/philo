/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:32:00 by felhafid          #+#    #+#             */
/*   Updated: 2024/08/11 15:53:27 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_function(t_data *p)
{
	int	i;

	pthread_mutex_destroy(&p->mutex_dead);
	pthread_mutex_destroy(&p->mutex_eat);
	pthread_mutex_destroy(&p->msg);
	i = 0;
	while (i < p->nb_philo)
	{
		pthread_mutex_destroy(p->forks[i]);
		i++;
	}
	free(p->philos);
	free2(p->forks, p->nb_philo);
}

void	free2(pthread_mutex_t **p, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

int	check_atoi(char *s, int nb, int i)
{
	if (!(s[i] >= '0' && s[i] <= '9') && s[i] != ' ' && s[i] != '\0')
		return (-1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\0')
			return (-1);
		i++;
	}
	if (nb == 0)
		return (-1);
	return (nb);
}

long	ft_atoi(char *s)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '-' || (s[i] == '+' && s[i + 1] == '+'))
		return (-1);
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb += s[i] - 48; 
		nb = nb * 10;
		if (nb > 2147483647 || nb < -2147483648)
			return (-1);
		i++;
	}
	nb = check_atoi(s, nb, i);
	if (nb == -1)
		return (-1);
	return (nb / 10);
}

int	mutex(t_data *p)
{
	pthread_mutex_lock(&p->mutex_dead);
	if (p->check_dead == 0)
	{
		pthread_mutex_unlock(&p->mutex_dead);
		return (-1);
	}
	pthread_mutex_unlock(&p->mutex_dead);
	return (0);
}
