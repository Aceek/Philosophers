/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:43:38 by ilinhard          #+#    #+#             */
/*   Updated: 2022/09/22 04:59:46 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_eat(t_philosopher *philo, t_conditions *rules)
{
	pthread_mutex_lock(&rules->forks[philo->lfork]);
	pthread_mutex_lock(&rules->forks[philo->rfork]);
	
}

void	*ft_routine(void *arg)
{
	t_philosopher	*philo;
	t_conditions	*rules;

	philo = (t_philosopher *)arg;
	rules = philo->rules;
	if (philo->id & 2)
		usleep(15000);
	while (!philo->state)
	{
		ft_eat(philo, rules);
		// ft_sleep();
		// ft_think();
	}
	return (NULL);
}

void	ft_start(t_conditions *rules)
{
	int					i;
	t_philosopher	*philo;

	i = 0;
	philo = rules->philo;
	rules->first_timer = ft_get_time();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, &ft_routine, &(philo[i])))
			return ;
		philo[i].time_last_meal = ft_get_time();
		i++;
	}
	// ft_death_cheaker(...);
	// exit_launcher(...);
}

int	main(int ac, char **av)
{
	t_conditions	rules;

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong numbers of args\n", 22), 1);
	if (ft_parsing(av, &rules))
		return (1);
	ft_start(&rules);
	return (0);
}
