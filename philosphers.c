/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:43:38 by ilinhard          #+#    #+#             */
/*   Updated: 2022/09/21 06:03:58 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// void	ft_start(t_conditions *rules)
// {
// 	int					i;
// 	t_philosopher	*philo;

// 	i = 0;
// 	philo = rules->philo;
// 	while (i < rules->nb_philo)
// 	{
// 		if (pthread_create(&(philo[i].thread_id), NULL, ft_routine, &philo[i]))
// 			return (1);
// 		i++;
// 	}
// }

int	main(int ac, char **av)
{
	t_conditions	rules;

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong numbers of args\n", 22), 1);
	if (ft_parsing(av, &rules))
		return (1);
	// ft_start(&rules);
	return (0);
}
