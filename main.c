/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felhafid <felhafid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:32:04 by felhafid          #+#    #+#             */
/*   Updated: 2024/08/12 10:57:22 by felhafid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	p;

	if (ac == 6 || ac == 5)
	{
		if (args(av, &p, ac) == -1)
			return (write(2, "Error: Invalid arguments.\n", 26), -1);
		if (setup_philos(&p) == -1)
		{
			free(p.philos);
			free2(p.forks, p.nb_philo);
			return (write(2, "Error: Failed to allocate memory\n", 33), -1);
		}
		if (create_threads(&p) == -1)
		{
			destroy_function(&p);
			return (-1);
		}
		destroy_function(&p);
	}
	else
		write(2, "Error: Invalid number of arguments.\n", 36);
	return (0);
}
