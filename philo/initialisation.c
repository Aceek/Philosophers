/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 02:39:08 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/11 04:10:17 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_mutex_init(t_conditions *rules)
{
	int				i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
		return (1);
	rules->verify_cleaning->malloc_forks_c = 1;
	i = -1;
	while (++i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (1);
		rules->verify_cleaning->forks_c += 1;
	}
	if (pthread_mutex_init(&rules->writing, NULL))
		return (1);
	rules->verify_cleaning->writing_c = 1;
	if (pthread_mutex_init(&rules->m_eating, NULL))
		return (1);
	rules->verify_cleaning->eating_c = 1;
	return (0);
}

int	ft_philo_init(t_conditions *rules, int nb_philo)
{
	int	i;

	rules->philo = malloc(sizeof(t_philosopher) * nb_philo);
	if (!rules->philo)
		return (1);
	rules->verify_cleaning->philo_c = 1;
	i = 0;
	while (i < nb_philo)
	{
		rules->philo[i].eating = 0;
		rules->philo[i].time_last_meal = 0;
		rules->philo[i].id = i;
		rules->philo[i].lfork = i;
		rules->philo[i].rfork = (i + 1) % nb_philo;
		rules->philo[i].eat_count = 0;
		rules->philo[i].rules = rules;
		i++;
	}
	return (0);
}

int	ft_parsing(char **av, t_conditions *rules)
{
	if (ft_init_cleaning(rules))
		return (1);
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_death = ft_atoi(av[2]);
	rules->time_eat = ft_atoi(av[3]);
	rules->time_sleep = ft_atoi(av[4]);
	rules->state = 0;
	if (rules->nb_philo < 1 || rules->time_death < 20
		|| rules->time_eat < 20 || rules->time_sleep < 20)
		return (1);
	if (av[5])
		rules->nb_eat = ft_atoi(av[5]);
	else
		rules->nb_eat = 0;
	if (rules->nb_eat < 0)
		return (1);
	if (ft_mutex_init(rules))
		return (write(2, "prob mutex init\n", 16), 1);
	if (ft_philo_init(rules, rules->nb_philo))
		return (write(2, "prob philo init\n", 16), 1);
	return (0);
}
