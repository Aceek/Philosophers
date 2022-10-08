/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 02:39:08 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/08 05:27:22 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_semaphore_init(t_conditions *rules)
{
	sem_unlink("forks_s");
	sem_unlink("eat_s");
	sem_unlink("writing_s");
	sem_unlink("test_s");
	rules->forks = sem_open("forks_s", O_CREAT, S_IRWXU, rules->nb_philo);
	rules->test = sem_open("test_s", O_CREAT, S_IRWXU, 1);
	rules->m_eating = sem_open("eat_s", O_CREAT, S_IRWXU, 1);
	rules->writing = sem_open("writing_s", O_CREAT, S_IRWXU, 1);
	if (rules->forks == SEM_FAILED || rules->m_eating == SEM_FAILED
		|| rules->writing == SEM_FAILED || rules->test == SEM_FAILED)
		return (1);
	return (0);
}

int	ft_philo_init(t_conditions *rules, int nb_philo)
{
	int	i;

	rules->philo = malloc(sizeof(t_philosopher) * nb_philo);
	if (!rules->philo)
		return (1);
	i = 0;
	while (i < nb_philo)
	{
		rules->philo[i].eating = 0;
		rules->philo[i].time_last_meal = 0;
		rules->philo[i].id = i;
		rules->philo[i].eat_count = 0;
		rules->philo[i].rules = rules;
		i++;
	}
	return (0);
}

int	ft_parsing(char **av, t_conditions *rules)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_death = ft_atoi(av[2]);
	rules->time_eat = ft_atoi(av[3]);
	rules->time_sleep = ft_atoi(av[4]);
	rules->state = 0;
	if (rules->nb_philo < 1 || rules->time_death < 0
		|| rules->time_eat < 0 || rules->time_sleep < 0)
		return (1);
	if (av[5])
		rules->nb_eat = ft_atoi(av[5]);
	else
		rules->nb_eat = 0;
	if (rules->nb_eat < 0)
		return (1);
	if (ft_semaphore_init(rules))
		return (write(2, "prob semaphores init\n", 21), 1);
	if (ft_philo_init(rules, rules->nb_philo))
		return (write(2, "prob philo init\n", 16), 1);
	return (0);
}
