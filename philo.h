/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:32:19 by felhafid          #+#    #+#             */
/*   Updated: 2024/08/12 10:58:11 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct philo
{
	int				id;
	int				state;
	long			last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct data		*d;
}t_philo;

typedef struct data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_time_eating;
	t_philo			*philos;
	pthread_mutex_t	**forks;
	int				check_dead;
	long			start;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	msg;
	pthread_mutex_t	mutex_dead;
	int				times_eaten;
	int				eat;
}t_data;

long	ft_atoi(char *s);
int		args(char **s, t_data *p, int ac);
int		setup_philos(t_data *p);
void	free2(pthread_mutex_t **p, int nb);
int		create_threads(t_data *p);
long	time_rn(void);
void	destroy_function(t_data *p);
int		eating(t_philo *p);
int		sleeping(t_philo *p);
int		mutex(t_data *p);
void	print_msg(t_data *d, t_philo *p, char *s);

#endif